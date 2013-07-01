#ifndef INCLUDE_TYPE_UTIL_H_
#define INCLUDE_TYPE_UTIL_H_

#include <iostream>  // std::cout
#include <string>    // std::string

// Conditionally include demangling headers for GCC/Clang
#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>  // abi::__cxa_demangle
#endif

namespace typeutil {

/**
 * @brief Demangles a compiler-mangled type name if possible
 * @param mangled The mangled type name from typeid
 * @return Demangled name if successful, original name otherwise
 *
 * Compiler Support:
 * - GCC/Clang: Uses __cxa_demangle
 * - Others: Returns original mangled name
 *
 * Memory Management:
 * - Allocates memory for demangled string which must be freed
 * - Converts to std::string for automatic cleanup
 */
inline std::string Demangle(const char* mangled) {
#if defined(__GNUC__) || defined(__clang__)
  int status = -1;
  char* demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
  if (status == 0) {
    std::string result(demangled);
    std::free(demangled);
    return result;
  }
  // Fall through to return mangled on failure
#endif
  return mangled;
}

// Forward declarations
template <typename T>
struct TypePrinter;

/**
 * @brief Provides base type names with demangling support
 * @tparam T Type to get name for
 *
 * Default implementation uses demangled typeid().name()
 * Specializations can override for specific types
 */
template <typename T>
struct TypeName {
  static std::string Get() { return Demangle(typeid(T).name()); }
};

// Specialize for common types to ensure consistent naming
template <>
struct TypeName<double> {
  static std::string Get() { return "double"; }
};
template <>
struct TypeName<int> {
  static std::string Get() { return "int"; }
};
template <>
struct TypeName<char> {
  static std::string Get() { return "char"; }
};
template <>
struct TypeName<bool> {
  static std::string Get() { return "bool"; }
};
template <>
struct TypeName<void> {
  static std::string Get() { return "void"; }
};

/**
 * @brief Recursively decomposes and prints types with qualifiers
 * @tparam T Type to print
 *
 * Processing Order (Critical for correct output):
 * 1. References (must come first to prevent misclassification)
 * 2. Pointers (handles nested pointers and pointer const)
 * 3. Non-pointer const qualifiers
 * 4. Base types (via TypeName)
 *
 * Qualifier Handling:
 * - References: Printed as suffix '&' after base type
 * - Pointers:
 *   * Ptr-to-const shows const before '*' (e.g. 'int const*')
 *   * Const-ptr shows const after '*' (e.g. 'int* const')
 * - Non-pointer const: Always printed as suffix 'const'
 *
 * @note Reference handling must precede pointer/const checks to maintain
 *       C++ type system semantics
 */
template <typename T>
struct TypePrinter {
  static void Print() {
    // Process reference types first - they have highest syntactic precedence
    if (std::is_reference<T>::value) {
      using NonRefType = typename std::remove_reference<T>::type;
      // Recursively print the referenced type (may have other qualifiers)
      TypePrinter<NonRefType>::Print();
      std::cout << " &";  // Append reference symbol
      return;  // Early return - references can't have additional qualifiers
    }
    // Handle pointer types first (including multi-level pointers)
    if (std::is_pointer<T>::value) {
      using PointeeType = typename std::remove_pointer<T>::type;
      // Recursively print pointed-to type (may be another pointer/const)
      TypePrinter<PointeeType>::Print();
      std::cout << " *";  // Space before star for readability

      // Handle pointer-level const (e.g., int* const)
      if (std::is_const<T>::value) {
        std::cout << " const";
      }
      return;
    }

    // Process non-pointer const types (references already handled)
    if (std::is_const<T>::value) {
      using NonConstType = typename std::remove_const<T>::type;
      // Print base type first then add const qualifier
      TypePrinter<NonConstType>::Print();
      std::cout << " const";  // Always suffix for consistency
      return;
    }

    // Base case - print fundamental/plain type name
    std::cout << TypeName<T>::Get();
  }
};

/**
 * @brief Primary interface for type printing
 * @tparam T Type to print to std::cout
 *
 * Usage:
 *   print_type<int>();        // prints "int"
 *   print_type<const int*>(); // prints "int const *"
 */
template <typename T>
void PrintType() {
  TypePrinter<T>::Print();
}

/**
 * @brief Prints variable name and its type
 * @tparam T Type of variable (automatically deduced)
 * @param var_name Variable name string
 *
 * Output Format:
 *   [var_name] : [human-readable type]
 */
template <typename T>
void PrintTypeInfo(const char* var_name) {
  std::cout << var_name << " : ";
  PrintType<T>();
  std::cout << std::endl;
}

/**
 * @brief Trait to detect if a type T supports output streaming (operator<<)
 * @tparam T Type to check
 *
 * Detection mechanism:
 * - Uses SFINAE and decltype to test if std::ostream << T is valid
 * - If valid, Test<T>(0) resolves to std::true_type
 * - Otherwise, falls back to std::false_type
 *
 * Usage:
 *   HasInsertionOperator<T>::kValue evaluates to true if T can be streamed
 */
template <typename T>
class HasInsertionOperator {
 private:
  // Preferred overload: succeeds if 'std::cout << U' is valid
  template <typename U>
  static auto Test(int)
      -> decltype(std::declval<std::ostream&>() << std::declval<U>(),
                  std::true_type());

  // Fallback overload: selected if preferred fails
  template <typename>
  static std::false_type Test(...);

 public:
  // Result: true if insertion operator is supported
  static constexpr bool kValue = decltype(Test<T>(0))::value;
};

/**
 * @brief Attempts to print the value of a variable if it supports operator<<
 * @tparam T Type of the variable
 * @param var The variable to print
 *
 * Enabled only if T supports insertion into std::ostream
 * Used in conjunction with SFINAE and HasInsertionOperator
 */
template <typename T>
typename std::enable_if<HasInsertionOperator<T>::kValue>::type
PrintValueIfPossible(const T& var) {
  std::cout << var;
}

/**
 * @brief Fallback when the type does not support operator<<
 * @tparam T Type of the variable
 * @param var The variable (unused)
 *
 * Prints placeholder text instead of value
 */
template <typename T>
typename std::enable_if<!HasInsertionOperator<T>::kValue>::type
PrintValueIfPossible(const T&) {
  std::cout << "<value not printable>";
}

}  // namespace typeutil

/**
 * @brief Macro to print variable name, value (if printable), and its type
 * @param var Variable to inspect
 *
 * Output Format:
 *   [var_name] : [value or <value not printable>] | type: [human-readable type]
 *
 * Example:
 *   PRINT_VAR_TYPE(my_var);
 *   Output: "my_var: 42 | type: int"
 *
 * Implementation:
 * 1. Uses #var to stringify the variable name
 * 2. Uses decltype to deduce its type
 * 3. Uses PrintValueIfPossible() to safely print value
 *    - Outputs actual value if operator<< is defined
 *    - Otherwise prints "<value not printable>"
 * 4. Uses PrintType() to print demangled, human-readable type
 * 5. Wraps entire logic in do-while(0) to ensure macro safety
 */
#define PRINT_VAR_TYPE(var)               \
  do {                                    \
    std::cout << #var << ": ";            \
    typeutil::PrintValueIfPossible(var);  \
    std::cout << " | type: ";             \
    typeutil::PrintType<decltype(var)>(); \
    std::cout << std::endl;               \
  } while (0)

#endif  // INCLUDE_TYPE_UTIL_H_

/*
 * const int variable_a = 0;
 * PRINT_VAR_TYPE(variable_a);  // int const
 *
 * const int* const variable_b = &variable_a;
 * PRINT_VAR_TYPE(variable_b);  // int const * const
 *
 * // Alternative explicit call
 * typeutil::PrintTypeInfo<decltype(variable_a)>("variable_a");
 *
 * PRINT_VAR_TYPE(L"abc");  // wchar_t [4]
 */