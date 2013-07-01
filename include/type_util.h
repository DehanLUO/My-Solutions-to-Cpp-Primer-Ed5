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
 * Processing Order:
 * 1. Pointers (handles nested pointers and pointer const)
 * 2. Non-pointer const qualifiers
 * 3. Base types (via TypeName)
 *
 * Const Handling:
 * - For non-pointers: Prints as "base_type const"
 * - For pointers: Const qualifiers on pointee are printed before '*'
 * - Pointer-level const is printed after '*' when present
 */
template <typename T>
struct TypePrinter {
  static void Print() {
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
    }
    // Handle non-pointer const types
    else if (std::is_const<T>::value) {
      using NonConstType = typename std::remove_const<T>::type;
      // Print base type first then add const qualifier
      TypePrinter<NonConstType>::Print();
      std::cout << " const";
    }
    // Base case: non-pointer, non-const type
    else {
      std::cout << TypeName<T>::Get();
    }
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

}  // namespace typeutil

/**
 * @brief Macro to print variable name and its type
 * @param var Variable to inspect (name and type)
 *
 * Example:
 *   PRINT_VAR_TYPE(my_var);
 *   Output: "my_var : int const *"
 *
 * Implementation:
 * 1. Stringizes variable name with #
 * 2. Uses decltype to get variable's type
 * 3. Wraps in do-while(0) for statement safety
 */
#define PRINT_VAR_TYPE(var)                        \
  do {                                             \
    std::cout << #var << ": " << var << "|type: "; \
    typeutil::PrintType<decltype(var)>();          \
    std::cout << std::endl;                        \
  } while (0)

#endif  // INCLUDE_TYPE_UTIL_H_

/*
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