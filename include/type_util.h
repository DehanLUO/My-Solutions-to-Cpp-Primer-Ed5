#ifndef INCLUDE_TYPE_UTIL_H_
#define INCLUDE_TYPE_UTIL_H_

/****************************
 * FILE OVERVIEW
 ****************************/
/**
 * @file type_util.h
 * @brief A C++ type introspection and debugging utility library
 *
 * This header provides comprehensive tools for runtime and compile-time
 * type inspection in C++. The library is designed with these key capabilities:
 *
 * 1. Type Name Formatting:
 *    - Human-readable type names with proper qualifier handling (const,
 * volatile, etc.)
 *    - Support for pointers, references, arrays, and complex template types
 *    - Compiler demangling for GCC/Clang (where available)
 *
 * 2. Value Printing:
 *    - Conditional value output based on streamability (operator<< support)
 *    - Special handling for character arrays and strings
 *    - Safe fallbacks for unprintable types
 *
 * 3. Type Information:
 *    - Size information (sizeof) with proper formatting
 *    - Array dimension analysis
 *    - Type trait detection
 *
 * 4. Debugging Utilities:
 *    - Convenience macros for variable inspection (PRINT_VAR_TYPE)
 *    - Compile-time size reporting (PRINT_TYPE_SIZE)
 *
 * The implementation uses modern C++ techniques including:
 * - Template metaprogramming
 * - SFINAE for capability detection
 * - Compile-time string processing
 * - Recursive template instantiation
 *
 * Example Usage:
 * @code
 * int x = 10;
 * const std::vector<double> vec{1.1, 2.2};
 *
 * PRINT_VAR_TYPE(x);    // Output: x: 10 | type: int
 * PRINT_VAR_TYPE(vec);  // Output: vec: <unprintable> | type:
 * std::vector<double> const PRINT_TYPE_SIZE(int); // Output: sizeof(int): 4
 * bytes
 * @endcode
 */

#include <array>     // std::array
#include <codecvt>   // std::wstring_convert, std::codecvt_utf8
#include <iostream>  // std::cout
#include <list>      // std::list
#include <map>       // std::map
#include <string>    // std::string
#include <utility>   // std::pair
#include <vector>    // std::vector

// Conditionally include demangling headers for GCC/Clang
#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>  // abi::__cxa_demangle
#endif

namespace typeutil {

// Forward declaration of TypeName template
template <typename T>
struct TypeName;

/****************************
 * BASIC UTILITY FUNCTIONS
 ****************************/
/**
 * The functions in this section provide fundamental capabilities that
 * support the rest of the library. They are ordered by dependency:
 * 1. Demangle - Core name processing needed by all other functions
 * 2. EscapeChar/EscapeWChar - Used by value printing functions
 * 3. OutputEscapedChar - Builds on EscapeChar
 * 4. EscapeString - Highest-level utility using all the above
 */

/**
 * @brief Demangles a compiler-generated type name into human-readable form
 *
 * This function processes mangled type names (from typeid().name()) into
 * readable format on supported compilers (GCC/Clang). The implementation:
 * 1. Validates input pointer (null check)
 * 2. Uses abi::__cxa_demangle for actual demangling
 * 3. Manages memory allocation/deallocation
 * 4. Handles all error cases gracefully
 *
 * @param mangled The mangled type name from typeid().name()
 * @return std::string containing either:
 *         - Demangled name (if successful)
 *         - Original mangled name (if demangling fails)
 *         - Empty string (if input is null)
 *
 * @note Only effective on GCC/Clang - returns input unchanged otherwise
 * @warning The returned string's lifetime is managed by std::string
 * @see TypeName template for higher-level type name handling
 */
inline std::string Demangle(const char* mangled) {
#if defined(__GNUC__) || defined(__clang__)
  int status = -1;  // Initialize status to error state

  // Check for null input to prevent undefined behaviour
  if (!mangled) return "";

  // Parameters for __cxa_demangle:
  // mangled - the mangled name to demangle
  // output_buffer - nullptr means the function will allocate memory
  // length - ignored when output_buffer is nullptr
  // status - reference to store the demangling status
  char* demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);

  // If demangling was successful (status == 0)
  if (status == 0) {
    std::string result(demangled);  // Convert to std::string
    std::free(demangled);           // Free the malloc'ed memory
    return result;
  }
  // Possible error status values:
  // -1: memory allocation failure
  // -2: invalid mangled name
  // -3: invalid arguments
#endif
  // Return original mangled name or empty string if input was null
  return mangled ? mangled : "";
}

/**
 * @brief Converts a character to its escaped string representation
 *
 * Handles all standard C escape sequences and provides readable output
 * for control characters. Used extensively in value printing logic.
 *
 * @param ch The character to escape
 * @return std::string containing either:
 *         - Standard escape sequence (\n, \t, etc.)
 *         - The literal character (if no escaping needed)
 *         - Hexadecimal escape for non-printable chars (future enhancement)
 *
 * @see EscapeWChar for wide character version
 * @see EscapeString for string-level escaping
 */
inline std::string EscapeChar(char ch) {
  switch (ch) {
    case '\0':
      return "\\0";
    case '\n':
      return "\\n";
    case '\t':
      return "\\t";
    case '\r':
      return "\\r";
    case '\"':
      return "\\\"";
    case '\\':
      return "\\\\";
    default:
      return std::string(1, ch);
  }
}

/**
 * @brief Converts a wide character to escaped UTF-8 representation
 *
 * Provides consistent escaping for wide characters, including:
 * - Standard control characters
 * - Unicode conversion via std::wstring_convert
 * - Fallback handling for conversion failures
 *
 * @param wch The wide character to process
 * @return std::string containing either:
 *         - Standard escape sequence
 *         - UTF-8 encoded character
 *         - "?" placeholder (on conversion failure)
 *
 * @note Uses exception handling for robust Unicode conversion
 * @see EscapeChar for narrow character version
 */
inline std::string EscapeWChar(wchar_t wch) {
  switch (wch) {
    case L'\0':
      return "\\0";
    case L'\n':
      return "\\n";
    case L'\t':
      return "\\t";
    case L'\r':
      return "\\r";
    case L'\"':
      return "\\\"";
    case L'\\':
      return "\\\\";
    default: {
      // Convert non-special wide characters to UTF-8
      std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
      try {
        // Attempt UTF-8 conversion of the wide character
        return converter.to_bytes(wch);
      } catch (...) {
        // Fallback for conversion failures (invalid wide char)
        return "?";
      }
    }
  }
}

/**
 * @brief Outputs an escaped character with proper array formatting
 *
 * Handles comma separation for array elements and delegates to EscapeChar
 * for actual escaping. Modifies the is_first flag to track array position.
 *
 * @param ch The character to output
 * @param is_first Reference to first-element flag (will be set to false)
 *
 * @note Designed for use in array printing contexts
 * @see PrintValueIfPossible for array value printing
 */
inline void OutputEscapedChar(char ch, bool& is_first) {
  if (!is_first) {
    std::cout << ", ";
  }
  is_first = false;
  std::cout << EscapeChar(ch);
}

/**
 * @brief Escapes all special characters in a string
 *
 * Processes each character in sequence using EscapeChar to produce
 * a fully escaped string suitable for display. Maintains original
 * string length when no escaping occurs.
 *
 * @param str The input string to process
 * @return std::string with all special characters properly escaped
 *
 * @see EscapeChar for individual character handling
 */
inline std::string EscapeString(const std::string& str) {
  std::string result;
  for (char ch : str) {
    result += EscapeChar(ch);
  }
  return result;
}

/****************************
 * ARRAY DIMENSION HANDLING
 ****************************/
/**
 * The ArrayInfo templates recursively extract array dimension information.
 * Ordering rationale:
 * 1. Primary template (base case) handles non-array types
 * 2. Specialization for T[N] handles actual arrays
 * This ordering allows recursive processing of multi-dimensional arrays.
 */

/**
 * @brief Primary template for array type introspection (base case)
 *
 * Serves as the recursion terminator for ArrayInfo processing. Provides:
 * - The input type as Base (no transformation)
 * - Empty AppendDims implementation (no dimensions to add)
 *
 * @tparam T The type to analyze (non-array case)
 */
template <typename T>
struct ArrayInfo {
  using Base = T;  ///< The base type (same as input for non-arrays)

  /**
   * @brief No dimensions to append for non-array types
   * @param dims The dimension vector (unmodified)
   */
  static void AppendDims(std::vector<size_t>&) {}
};

/**
 * @brief Specialization for array types (recursive case)
 *
 * Handles array dimension extraction through recursive template instantiation.
 * For each T[N] array:
 * 1. Recursively processes element type T to find base type
 * 2. Appends dimension N to the dimension list
 * 3. Continues recursion for multi-dimensional arrays
 *
 * @tparam T The array element type
 * @tparam N The array dimension size
 *
 * @note Dimensions are collected in declaration order (left-to-right)
 * @see TypeName specializations that use this for array type formatting
 */
template <typename T, size_t N>
struct ArrayInfo<T[N]> {
  using Base = typename ArrayInfo<T>::Base;  ///< Recursively get base type

  /**
   * @brief Appends this array's dimension and continues recursion
   * @param dims The dimension vector to append to (modified in-place)
   *
   * Note: Dimensions are collected in declaration order (left-to-right in
   * type). For `int[2][3]`, the recursion order is:
   * 1. `ArrayInfo<int[2][3]>::AppendDims()` → pushes 2
   * 2. `ArrayInfo<int[3]>::AppendDims()`   → pushes 3
   * 3. `ArrayInfo<int>::AppendDims()`      → base case, no-op
   * Result: dims = {2, 3} (matches declaration order)
   */
  static void AppendDims(std::vector<size_t>& dims) {
    // First append our dimension (outermost dimension comes first)
    dims.push_back(N);
    // Then recurse to handle inner dimensions
    ArrayInfo<T>::AppendDims(dims);
  }
};

/****************************
 * CORE TYPE NAME HANDLING
 ****************************/
/**
 * The TypeName system provides human-readable type names through template
 * specialization. Implementation structure:
 * 1. Fundamental type specializations (void, int, etc.)
 * 2. Qualifier handling (const, volatile)
 * 3. Compound type handling (pointers, references, arrays)
 * 4. STL container support (std::string, std::map)
 */

namespace detail {

/**
 * @brief Primary template for type name implementation (fallback case)
 *
 * Provides default type name handling using compiler demangling when no
 * specialization exists. Serves as the base case for SFINAE-based detection.
 *
 * @tparam T The type to name
 * @tparam void SFINAE enabler (default void)
 *
 * @return std::string containing:
 *         - Demangled type name if available
 *         - Original mangled name in parentheses if demangling fails
 */
template <typename T, typename = void>
struct TypeNameImpl {
  static std::string Get() { return '(' + Demangle(typeid(T).name()) + ')'; }
};

// Fundamental type specializations
/**
 * @brief Specialization for void type
 *
 * Explicitly handles the void type case to avoid demangling overhead and
 * provide consistent formatting.
 *
 * @return Always returns "void"
 */
template <>
struct TypeNameImpl<void> {
  static std::string Get() { return "void"; }
};

/**
 * @brief Specialization for bool type
 *
 * Provides explicit naming for boolean type to ensure consistent output
 * across platforms and compilers.
 *
 * @return Always returns "bool"
 */
template <>
struct TypeNameImpl<bool> {
  static std::string Get() { return "bool"; }
};

/**
 * @brief Specialization for char type
 *
 * Provides explicit naming for character type to ensure consistent output
 * across platforms and compilers.
 *
 * @return Always returns "char"
 */
template <>
struct TypeNameImpl<char> {
  static std::string Get() { return "char"; }
};

/**
 * @brief Specialization for wchar_t type
 *
 * Provides explicit naming for wide character type to ensure consistent output
 * across platforms and compilers.
 *
 * @return Always returns "wchar_t"
 */
template <>
struct TypeNameImpl<wchar_t> {
  static std::string Get() { return "wchar_t"; }
};

/**
 * @brief Specialization for unsigned int type
 *
 * Provides explicit naming for unsigned integer type to ensure consistent
 * output across platforms and compilers.
 *
 * @return Always returns "unsigned"
 */
template <>
struct TypeNameImpl<unsigned> {
  static std::string Get() { return "unsigned"; }
};

/**
 * @brief Specialization for int type
 *
 * Provides explicit naming for integer type to ensure consistent output
 * across platforms and compilers.
 *
 * @return Always returns "int"
 */
template <>
struct TypeNameImpl<int> {
  static std::string Get() { return "int"; }
};

/**
 * @brief Specialization for long type
 *
 * Provides explicit naming for long integer type to ensure consistent output
 * across platforms and compilers.
 *
 * @return Always returns "long"
 */
template <>
struct TypeNameImpl<long> {
  static std::string Get() { return "long"; }
};

/**
 * @brief Specialization for unsigned long type
 *
 * Provides explicit naming for unsigned long integer type to ensure consistent
 * output across platforms and compilers.
 *
 * @return Always returns "unsigned long"
 */
template <>
struct TypeNameImpl<unsigned long> {
  static std::string Get() { return "unsigned long"; }
};

/**
 * @brief Specialization for float type
 *
 * Provides explicit naming for single-precision floating point type to ensure
 * consistent output across platforms and compilers.
 *
 * @return Always returns "float"
 */
template <>
struct TypeNameImpl<float> {
  static std::string Get() { return "float"; }
};

/**
 * @brief Specialization for double type
 *
 * Provides explicit naming for double-precision floating point type to ensure
 * consistent output across platforms and compilers.
 *
 * @return Always returns "double"
 */
template <>
struct TypeNameImpl<double> {
  static std::string Get() { return "double"; }
};

/**
 * @brief Specialization for long double type
 *
 * Provides explicit naming for extended-precision floating point type to ensure
 * consistent output across platforms and compilers.
 *
 * @return Always returns "long double"
 */
template <>
struct TypeNameImpl<long double> {
  static std::string Get() { return "long double"; }
};

/**
 * @brief Specialization for std::string type
 *
 * Provides explicit naming for standard string type to ensure consistent output
 * across platforms and compilers.
 *
 * @return Always returns "std::string"
 */
template <>
struct TypeNameImpl<std::string> {
  static std::string Get() { return "std::string"; }
};

/**
 * @brief Specialization for const-qualified types (non-array)
 *
 * Handles const qualification for non-array types by appending " const"
 * to the base type name. Uses SFINAE to exclude array types.
 *
 * @tparam T The base type to qualify
 * @return std::string containing base type name with " const" suffix
 *
 * @note The qualifier position matches natural reading order (e.g., "int
 * const")
 */
template <typename T>
struct TypeNameImpl<const T,
                    typename std::enable_if<!std::is_array<T>::value>::type> {
  static std::string Get() { return TypeName<T>::Get() + " const"; }
};

/**
 * @brief Specialization for pointer types
 *
 * Formats pointer types by appending " *" to the pointed-to type name.
 * Maintains proper spacing for readability.
 *
 * @tparam T The pointed-to type
 * @return std::string containing base type name with " *" suffix
 */
template <typename T>
struct TypeNameImpl<T*> {
  static std::string Get() { return TypeName<T>::Get() + " *"; }
};

/**
 * @brief Specialization for lvalue reference types
 *
 * Formats reference types by appending " &" to the referenced type name.
 * Distinguishes from pointer types with different spacing.
 *
 * @tparam T The referenced type
 * @return std::string containing base type name with " &" suffix
 */
template <typename T>
struct TypeNameImpl<T&> {
  static std::string Get() { return TypeName<T>::Get() + " &"; }
};

/**
 * @brief Specialization for rvalue reference types
 *
 * Formats rvalue references by appending " &&" to the referenced type name.
 * Clearly distinguishes from lvalue references.
 *
 * @tparam T The referenced type
 * @return std::string containing base type name with " &&" suffix
 */
template <typename T>
struct TypeNameImpl<T&&> {
  static std::string Get() { return TypeName<T>::Get() + " &&"; }
};

/**
 * @brief Specialization for const character arrays (string literals)
 *
 * Provides formatted naming for string literals (const char[N]) including
 * the array size in the type name.
 *
 * @tparam N The array size including null terminator
 * @return std::string formatted as "const char[N]"
 */
template <size_t N>
struct TypeNameImpl<const char[N]> {
  static std::string Get() { return "const char[" + std::to_string(N) + "]"; }
};

/**
 * @brief Specialization for const wide character arrays
 *
 * Provides formatted naming for wide string literals (const wchar_t[N])
 * including the array size in the type name.
 *
 * @tparam N The array size including null terminator
 * @return std::string formatted as "const wchar_t[N]"
 */
template <size_t N>
struct TypeNameImpl<const wchar_t[N]> {
  static std::string Get() {
    return "const wchar_t[" + std::to_string(N) + "]";
  }
};

/**
 * @brief Specialization for arrays of pointers (T*[N])
 *
 * Handles formatting of pointer arrays by:
 * 1. Getting the base pointer type name
 * 2. Appending array dimensions in declaration order
 *
 * @tparam T The pointed-to type
 * @tparam N The array dimension
 * @return Formatted type name (e.g., "int *[5]" for int*[5])
 */
template <typename T, size_t N>
struct TypeNameImpl<T* [N]> {
  static std::string Get() {
    std::vector<size_t> dims;
    ArrayInfo<T* [N]>::AppendDims(dims);
    std::string result = TypeName<T>::Get() + " *";
    for (size_t d : dims) result += "[" + std::to_string(d) + "]";
    return result;
  }
};

/**
 * @brief Specialization for regular arrays (T[N])
 *
 * Formats array types by:
 * 1. Getting the base type name
 * 2. Appending all array dimensions in declaration order
 *
 * @tparam T The array element type
 * @tparam N The array dimension
 * @return Formatted type name (e.g., "int[3][4]" for int[3][4])
 */
template <typename T, size_t N>
struct TypeNameImpl<T[N]> {
  static std::string Get() {
    std::vector<size_t> dims;
    ArrayInfo<T[N]>::AppendDims(dims);
    std::string result = TypeName<typename ArrayInfo<T[N]>::Base>::Get();
    for (size_t d : dims) result += "[" + std::to_string(d) + "]";
    return result;
  }
};

/**
 * @brief Specialization for const pointers (T* const)
 *
 * Formats const pointers by:
 * 1. Getting the base type name
 * 2. Appending " * const" qualifier
 *
 * @tparam T The pointed-to type
 * @return Formatted type name (e.g., "int * const")
 */
template <typename T>
struct TypeNameImpl<T* const> {
  static std::string Get() { return TypeName<T>::Get() + " * const"; }
};

/**
 * @brief Specialization for arrays of const pointers to const (const T*
 * const[N])
 *
 * Handles complex const-qualified pointer arrays by:
 * 1. Getting the base type name
 * 2. Adding const qualifiers in correct positions
 * 3. Appending array dimensions
 *
 * @tparam T The pointed-to type
 * @tparam N The array dimension
 * @return Formatted type name (e.g., "int const * const[5]")
 */
template <typename T, size_t N>
struct TypeNameImpl<const T* const[N]> {
  static std::string Get() {
    std::vector<size_t> dims;
    ArrayInfo<const T* const[N]>::AppendDims(dims);
    std::string result = TypeName<T>::Get() + " const * const";
    for (size_t d : dims) result += "[" + std::to_string(d) + "]";
    return result;
  }
};

/**
 * @brief Specialization for arrays of const pointers (T* const[N])
 *
 * Formats arrays where the pointers themselves are const by:
 * 1. Getting the base type name
 * 2. Adding pointer const qualifier
 * 3. Appending array dimensions
 *
 * @tparam T The pointed-to type
 * @tparam N The array dimension
 * @return Formatted type name (e.g., "int * const[5]")
 */
template <typename T, size_t N>
struct TypeNameImpl<T* const[N]> {
  static std::string Get() {
    std::vector<size_t> dims;
    ArrayInfo<T* const[N]>::AppendDims(dims);
    std::string result = TypeName<T>::Get() + " * const";
    for (size_t d : dims) result += "[" + std::to_string(d) + "]";
    return result;
  }
};

/**
 * @brief Specialization for std::map container
 *
 * Provides formatted naming for std::map instantiations including proper
 * template parameter naming. Handles nested template types recursively.
 *
 * @tparam K The map key type
 * @tparam V The map value type
 * @return std::string formatted as "std::map<KeyType, ValueType>"
 */
template <typename K, typename V>
struct TypeNameImpl<std::map<K, V>> {
  static std::string Get() {
    return "std::map<" + TypeName<K>::Get() + ", " + TypeName<V>::Get() + ">";
  }
};

/**
 * @brief Specialization for std::vector container
 *
 * Provides formatted naming for std::vector instantiations including proper
 * template parameter naming. Handles nested template types recursively.
 *
 * @tparam T The vector element type
 * @return std::string formatted as "std::vector<ElementType>"
 */
template <typename T>
struct TypeNameImpl<std::vector<T>> {
  static std::string Get() { return "std::vector<" + TypeName<T>::Get() + ">"; }
};

/**
 * @brief Specialization for std::array container
 *
 * Provides formatted naming for std::array instantiations including both
 * the element type and array size in the type name.
 *
 * @tparam T The array element type
 * @tparam N The array size (compile-time constant)
 * @return std::string formatted as "std::array<ElementType, Size>"
 */
template <typename T, size_t N>
struct TypeNameImpl<std::array<T, N>> {
  static std::string Get() {
    return "std::array<" + TypeName<T>::Get() + ", " + std::to_string(N) + ">";
  }
};

/**
 * @brief Specialization for std::pair container
 *
 * Provides formatted naming for std::pair instantiations including both
 * the first and second template parameters in the type name.
 *
 * @tparam T1 The type of the first element
 * @tparam T2 The type of the second element
 * @return std::string formatted as "std::pair<FirstType, SecondType>"
 */
template <typename T1, typename T2>
struct TypeNameImpl<std::pair<T1, T2>> {
  static std::string Get() {
    return "std::pair<" + TypeName<T1>::Get() + ", " + TypeName<T2>::Get() +
           ">";
  }
};

/**
 * @brief Specialization for std::list container
 *
 * Provides formatted naming for std::list instantiations including proper
 * template parameter naming. Handles nested template types recursively.
 *
 * @tparam T The list element type
 * @return std::string formatted as "std::list<ElementType>"
 */
template <typename T>
struct TypeNameImpl<std::list<T>> {
  static std::string Get() { return "std::list<" + TypeName<T>::Get() + ">"; }
};

}  // namespace detail

// Specializations for Compound Types

/**
 * @brief Specialization for const-qualified types.
 *
 * Handles all const-qualified types with special consideration for array types.
 *
 * Design Rationale:
 * - Proper const qualification is fundamental to C++'s type system
 * - Arrays require distinct handling because:
 *   - The const qualifier applies to elements, not the array itself
 *   - Array dimensions must be preserved in the type name
 * - Maintains consistency with declaration syntax (e.g., "const int[5]")
 *
 * Implementation Details:
 * 1. Type classification:
 *    - Uses std::is_array to detect array types
 *    - Non-arrays receive straightforward const qualification
 *
 * 2. Array handling:
 *    - Extracts the underlying type using std::remove_extent
 *    - Preserves array size information using std::extent
 *    - Formats as "const BaseType[size]" to reflect actual semantics
 *
 * 3. Non-array handling:
 *    - Appends " const" to maintain natural reading order
 *    - Matches how const appears in variable declarations
 *
 * Template Metaprogramming Notes:
 * - std::is_array<T>::value provides array detection
 * - std::remove_extent<T>::type yields the element type
 * - std::extent<T>::value retrieves the array dimension
 * - All operations are evaluated at compile-time
 *
 * @tparam T The base type being qualified (may be array or non-array)
 * @return Properly formatted type name with const qualification
 */

template <typename T>
struct TypeName {
  static std::string Get() { return detail::TypeNameImpl<T>::Get(); }
};

/**
 * @brief Specialization for pointer types
 */
template <typename T>
struct TypeName<T*> {
  static std::string Get() { return TypeName<T>::Get() + " *"; }
};

/**
 * @brief Specialization for lvalue reference types
 */
template <typename T>
struct TypeName<T&> {
  static std::string Get() { return TypeName<T>::Get() + " &"; }
};

/**
 * @brief Specialization for rvalue reference types
 */
template <typename T>
struct TypeName<T&&> {
  static std::string Get() { return TypeName<T>::Get() + " &&"; }
};

// ===== ARRAY AND CONST-QUALIFIED TYPE HANDLING =====
// These specializations must appear after the primary template but before other
// specializations (like pointers/references) to ensure proper matching
// priority.

/**
 * @brief Specialization for constant character arrays (string literals).
 *
 * This handles C-style string literals like "hello" which have type const
 * char[N].
 *
 * Rationale:
 * - String literals are fundamental in C++ and deserve explicit formatting
 * - We want to clearly distinguish between mutable and literal strings
 * - The standard mandates that string literals are const-qualified
 *
 * @tparam N The array size including null terminator
 * @return Formatted type name (e.g., "const char[6]" for "hello")
 */
template <size_t N>
struct TypeName<const char[N]> {
  static std::string Get() { return "const char[" + std::to_string(N) + "]"; }
};

/**
 * @brief Specialization for wide character string literals (const wchar_t[N]).
 *
 * Handles wide string literals like L"text" similarly to narrow strings.
 *
 * Rationale:
 * - Wide strings are used in internationalization and Windows programming
 * - They follow the same const qualification rules as char strings
 * - Explicit specialization prevents ambiguity with regular arrays
 *
 * @tparam N The array size including null terminator
 * @return Formatted type name (e.g., "const wchar_t[3]" for L"hi")
 */
template <size_t N>
struct TypeName<const wchar_t[N]> {
  static std::string Get() {
    return "const wchar_t[" + std::to_string(N) + "]";
  }
};

/**
 * @brief Specialization for pointer arrays (T*[N])
 */
template <typename T, size_t N>
struct TypeName<T* [N]> {
  static std::string Get() {
    std::vector<size_t> dims;
    ArrayInfo<T* [N]>::AppendDims(dims);

    std::string result = TypeName<T>::Get() + " *";
    for (size_t d : dims) {
      result += "[" + std::to_string(d) + "]";
    }
    return result;
  }
};

/**
 * @brief Specialization for regular arrays of any type (T[N]).
 *
 * Handles all array types except those already specialized above.
 *
 * Rationale:
 * - Arrays decay to pointers in most contexts but we want to preserve size info
 * - The standard format Type[size] matches declaration syntax
 * - Specializing separately from pointers maintains type system accuracy
 *
 * Implementation Notes:
 * - Recursively gets the base type name (T) then appends dimensions
 * - Handles multi-dimensional arrays naturally (e.g., int[3][4])
 *
 * @tparam T The array element type
 * @tparam N The array size
 * @return Formatted type name (e.g., "int[5]" or "float[2][3]")
 */
template <typename T, size_t N>
struct TypeName<T[N]> {
  static std::string Get() {
    std::vector<size_t> dims;
    ArrayInfo<T[N]>::AppendDims(dims);

    std::string result = TypeName<typename ArrayInfo<T[N]>::Base>::Get();
    for (size_t d : dims) {
      result += "[" + std::to_string(d) + "]";
    }
    return result;
  }
};

/**
 * @brief Specialization for const pointers (T* const)
 */
template <typename T>
struct TypeName<T* const> {
  static std::string Get() { return TypeName<T>::Get() + " * const"; }
};

/**
 * @brief Specialization for const pointer arrays (const T* const[N])
 */
template <typename T, size_t N>
struct TypeName<const T* const[N]> {
  static std::string Get() {
    std::vector<size_t> dims;
    ArrayInfo<const T* const[N]>::AppendDims(dims);

    std::string result = TypeName<T>::Get() + " const * const";
    for (size_t d : dims) {
      result += "[" + std::to_string(d) + "]";
    }
    return result;
  }
};

/**
 * @brief Specialization for pointer arrays with const array (T* const[N])
 */
template <typename T, size_t N>
struct TypeName<T* const[N]> {
  static std::string Get() {
    std::vector<size_t> dims;
    ArrayInfo<T* const[N]>::AppendDims(dims);

    std::string result = TypeName<T>::Get() + " * const";
    for (size_t d : dims) {
      result += "[" + std::to_string(d) + "]";
    }
    return result;
  }
};

/****************************
 * TYPE PRINTING CAPABILITY DETECTION
 ****************************/
/**
 * This section implements SFINAE-based detection of stream insertion
 * capability (operator<<). The implementation order is:
 * 1. HasInsertionOperator class template (main detection logic)
 * 2. Test functions (SFINAE implementation details)
 */

/**
 * @brief Trait class for detecting stream insertion operator support
 *
 * Uses SFINAE to determine if a type T can be output via operator<<.
 * The implementation provides:
 * - Compile-time boolean kValue indicating capability
 * - Clean SFINAE failure for non-streamable types
 *
 * @tparam T The type to check for stream insertion support
 *
 * Implementation Notes:
 * - Uses decltype and expression SFINAE in Test function
 * - Provides kValue as static constexpr bool
 * - Maintains compatibility with C++11 and later
 *
 * Example Usage:
 * @code
 * static_assert(HasInsertionOperator<std::string>::kValue,
 *               "Strings should be streamable");
 * @endcode
 */
template <typename T>
class HasInsertionOperator {
 private:
  /**
   * @brief Test function that checks for operator<< support
   * @return std::true_type if operator<< exists, otherwise substitution fails
   */
  template <typename U>
  static auto Test(int)
      -> decltype(std::declval<std::ostream&>() << std::declval<U>(),
                  std::true_type());

  /**
   * @brief Fallback test function that always matches
   * @return std::false_type
   */
  template <typename>
  static std::false_type Test(...);

 public:
  /// Boolean value indicating whether T supports operator<<
  static constexpr bool kValue = decltype(Test<T>(0))::value;
};

/****************************
 * VALUE PRINTING LOGIC
 ****************************/
/**
 * The PrintValueIfPossible functions handle conditional value output based on:
 * 1. Stream insertion capability (operator<<)
 * 2. Type category (fundamental, pointer, array, etc.)
 *
 * Function ordering rationale:
 * 1. Primary template (most general case)
 * 2. Specializations for specific types (std::string, pointers, arrays)
 * 3. Fallback handlers (unprintable types)
 */

/**
 * @brief Primary template for conditional value printing
 *
 * Prints values only if:
 * 1. The type supports operator<<
 * 2. Is not an array type
 * 3. Is not a pointer type
 *
 * @tparam T The type to print
 * @param var The value to output
 *
 * @note Uses SFINAE to disable instantiation for unsupported types
 * @see HasInsertionOperator for capability detection
 */
template <typename T>
typename std::enable_if<HasInsertionOperator<T>::kValue  //
                        && !std::is_array<T>::value      //
                        && !std::is_pointer<T>::value>::type
PrintValueIfPossible(const T& var) {
  std::cout << var;  // Print the value using operator<<
}

/**
 * @brief Specialization for std::string to handle array-style output
 */
template <>
void PrintValueIfPossible<std::string>(const std::string& var) {
  std::cout << EscapeString(var);
}

/**
 * @brief Prints a character array in [elem, elem, ...] format with proper
 * escaping
 *
 * Outputs all elements of the character array including null terminators,
 * with special characters escaped. Maintains standard array formatting.
 *
 * @tparam N Size of the character array (automatically deduced)
 * @param arr Reference to the character array
 *
 * @note Null terminators are displayed as "\0"
 */
template <size_t N>
void PrintValueIfPossible(const char (&arr)[N]) {
  std::cout << '[';      // Open array bracket
  bool is_first = true;  // Track first element for comma placement

  // Iterate through all array elements (including null terminators)
  for (size_t i = 0; i < N; ++i) {
    if (!is_first) {
      std::cout << ", ";  // Add separator before all elements except first
    }
    is_first = false;

    // Output properly escaped character representation
    std::cout << EscapeChar(arr[i]);
  }

  std::cout << ']';  // Close array bracket
}

/**
 * @brief Prints a wide character array in [elem, elem, ...] format with UTF-8
 * encoding
 *
 * Outputs all elements of the wide character array including null terminators,
 * with special characters escaped and proper Unicode conversion.
 *
 * @tparam N Size of the wide character array (automatically deduced)
 * @param arr Reference to the wide character array
 *
 * @note Null terminators are displayed as "\0"
 * @note Non-ASCII characters are converted to UTF-8
 */
template <size_t N>
void PrintValueIfPossible(const wchar_t (&arr)[N]) {
  std::cout << '[';      // Open array bracket
  bool is_first = true;  // Track first element for comma placement

  // Iterate through all array elements (including null terminators)
  for (size_t i = 0; i < N; ++i) {
    if (!is_first) {
      std::cout << ", ";  // Add separator before all elements except first
    }
    is_first = false;

    // Convert wide character to escaped UTF-8 representation
    std::string escaped = EscapeWChar(arr[i]);

    // Output the complete escaped character sequence
    std::cout << escaped;
  }

  std::cout << ']';  // Close array bracket
}

/**
 * @brief Specialization for pointer types
 */
template <typename T>
typename std::enable_if<std::is_pointer<T>::value>::type PrintValueIfPossible(
    const T& var) {
  std::cout << '(' << var << ')';  // Generic pointer representation
}

/**
 * @brief Specialization for arrays
 */
template <typename T, size_t N>
typename std::enable_if<
    !std::is_same<typename std::remove_cv<T>::type, char>::value &&
    !std::is_same<typename std::remove_cv<T>::type, wchar_t>::value &&
    HasInsertionOperator<T>::kValue>::type
PrintValueIfPossible(const T (&arr)[N]) {
  std::cout << '[';
  for (size_t i = 0; i < N; ++i) {
    if (i != 0) std::cout << ", ";
    PrintValueIfPossible(arr[i]);
  }
  std::cout << ']';
}

/**
 * @brief Specialized handler for arrays of types that cannot be printed
 * directly.
 *
 * This function template is triggered for arrays of types that:
 * 1. Are NOT character arrays (neither char nor wchar_t)
 * 2. Do NOT have an available stream insertion operator (operator<<)
 *
 * Instead of attempting to print the array elements (which would fail), it
 * outputs a descriptive placeholder showing the array type and size in the
 * format:
 *   [<array of TYPE_NAME>]
 *
 * Examples of types that would trigger this version:
 * - Arrays of custom structs/classes without operator<<
 * - Arrays of STL containers without operator<< specialization
 * - Arrays of function pointers
 * - Arrays of complex nested types
 *
 * @tparam T The element type of the array (automatically deduced)
 * @tparam N The size of the array (automatically deduced)
 * @param arr The array reference to process
 *
 * @note This is a fallback handler that ensures type safety when printing
 * arrays. It prevents compilation errors while still providing useful type
 * information.
 * @see HasInsertionOperator for the streamability detection mechanism
 */
template <typename T, size_t N>
typename std::enable_if<
    !std::is_same<typename std::remove_cv<T>::type, char>::value &&
    !std::is_same<typename std::remove_cv<T>::type, wchar_t>::value &&
    !HasInsertionOperator<T>::kValue>::type
PrintValueIfPossible(const T (&arr)[N]) {
  std::cout << "[<array of " << TypeName<T>::Get() << ">]";
}

/**
 * @brief Fallback printer for unprintable types (no `operator<<` defined).
 */
template <typename T>
typename std::enable_if<!HasInsertionOperator<T>::kValue>::type
PrintValueIfPossible(const T&) {
  std::cout << "<unprintable>";
}

/****************************
 * TYPE PRINTING INTERFACES
 ****************************/
/**
 * Public-facing interfaces for type information display. The components are:
 * 1. TypePrinter - Internal formatting helper
 * 2. PrintType - Direct type name output
 * 3. PrintTypeInfo - Variable name + type output
 *
 * These build on the core type name handling infrastructure while providing
 * user-friendly interfaces.
 */

/**
 * @brief Internal type printing helper class
 *
 * Provides centralized control over type name formatting and output.
 * Can be specialized for custom formatting requirements.
 *
 * @tparam T The type to format and print
 *
 * @note Designed for extension - specialize to customize output
 */
template <typename T>
struct TypePrinter {
  /**
   * @brief Prints the type name to std::cout
   */
  static void Print() {
    std::cout << TypeName<T>::Get();  // Output the type name
  }
};

/**
 * @brief Public interface for printing the type of T to `std::cout`.
 *
 * @tparam T Type whose name is to be printed.
 *
 * Example:
 * ```cpp
 * PrintType<const int*>();  // prints: int const *
 * ```
 */
template <typename T>
void PrintType() {
  TypePrinter<T>::Print();
}

/**
 * @brief Prints a variable's name and its type.
 *
 * @tparam T Type of the variable (inferred automatically).
 * @param var_name The name of the variable (as a string literal).
 *
 * Output format:
 *   variable_name : readable_type
 */
template <typename T>
void PrintTypeInfo(const char* var_name) {
  std::cout << var_name << " : ";
  PrintType<T>();
  std::cout << '\n';
}

/****************************
 * TYPE SIZE INFORMATION
 ****************************/
/**
 * Compile-time size reporting utilities. The implementation provides:
 * 1. TypeSize template - Core size information handler
 * 2. PrintTypeSize function - Convenience interface
 *
 * These components work with the type name system to provide formatted
 * size information including proper type names.
 */

/**
 * @brief Compile-time type size analyzer
 *
 * Provides both printing and string-based access to type size information.
 * Integrates with TypeName system for consistent type naming.
 *
 * @tparam T The type to analyze
 *
 * @note All operations are evaluated at compile-time
 */
template <typename T>
struct TypeSize {
  /**
   * @brief Prints the size of the type in bytes
   * @details Output format: "sizeof(type_name): X bytes"
   */
  static void Print() {
    std::cout << "sizeof(" << TypeName<T>::Get() << "): " << sizeof(T)
              << " bytes";
  }

  /**
   * @brief Gets the size of the type as a string
   * @return std::string containing size information
   */
  static std::string Get() {
    return "sizeof(" + TypeName<T>::Get() + "): " + std::to_string(sizeof(T)) +
           " bytes";
  }
};

/**
 * @brief Public interface for printing type size information
 * @tparam T The type whose size to print
 */
template <typename T>
void PrintTypeSize() {
  TypeSize<T>::Print();
}

}  // namespace typeutil

/****************************
 * DEBUGGING MACROS
 ****************************/
/**
 * Convenience macros for common debugging tasks. These macros:
 * 1. Provide consistent output formatting
 * 2. Handle all type introspection automatically
 * 3. Are safe for use in most contexts (use do/while(0) idiom)
 *
 * The macros are designed to be minimal yet flexible, building on the
 * full capabilities of the typeutil library.
 */

/**
 * @def PRINT_VAR_TYPE(var)
 * @brief Inspects and prints a variable's name, value and type
 *
 * Provides comprehensive variable introspection in a single macro:
 * - Variable name (as written in source)
 * - Current value (if printable)
 * - Full type information (with qualifiers)
 *
 * Output format:
 *   var_name: var_value | type: readable_type
 *
 * Behaviour:
 * - Uses `decltype` to deduce the type
 * - Prints the value only if the type supports `operator<<`
 * - Uses typeutil's internal demangling/type-name tools for display
 *
 * @param var The variable to inspect (any type)
 *
 * Example:
 * @code
 * const int x = 5;
 * PRINT_VAR_TYPE(x);  // Output: x: 5 | type: int
 * @endcode
 *
 * @note Value printing depends on operator<< availability
 */
#define PRINT_VAR_TYPE(var)               \
  do {                                    \
    std::cout << #var << ": ";            \
    typeutil::PrintValueIfPossible(var);  \
    std::cout << " |type: ";              \
    typeutil::PrintType<decltype(var)>(); \
    std::cout << '\n';                    \
  } while (0)

/**
 * @def PRINT_TYPE_SIZE(type)
 * @brief Prints the byte size of a type
 *
 * Provides compile-time size information with proper type naming.
 * Works with all types including:
 * - Fundamental types (int, double, etc.)
 * - Compound types (structs, classes)
 * - Template instantiations
 *
 * Output format:
 *   sizeof(type_name): X bytes
 *
 * @param type The type to examine (can be a built-in or user-defined type)
 *
 * Example:
 * @code
 * PRINT_TYPE_SIZE(int);    // Output: sizeof(int): 4 bytes
 * PRINT_TYPE_SIZE(double); // Output: sizeof(double): 8 bytes
 * @endcode
 */
#define PRINT_TYPE_SIZE(type)        \
  do {                               \
    typeutil::PrintTypeSize<type>(); \
    std::cout << '\n';               \
  } while (0)

#endif  // INCLUDE_TYPE_UTIL_H_
