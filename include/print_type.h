#ifndef INCLUDE_PRINT_TYPE_H_
#define INCLUDE_PRINT_TYPE_H_

#include <cxxabi.h>  // abi::__cxa_demangle

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Retrieves human-readable type name by demangling compiler-encoded type
 * info
 * @tparam T Type to be examined
 * @return Demangled type name if successful, raw name otherwise
 *
 * Execution Flow:
 * 1. Gets compiler-encoded type name via typeid().name()
 * 2. Attempts to demangle the name using compiler-specific ABI
 * 3. Returns demangled result if successful, falls back to raw name
 * 4. Manually frees memory allocated by demangling function
 *
 * @note Requires compiler support (GCC/Clang: __cxa_demangle)
 * @warning Returned string may contain template parameters/special characters
 */
template <typename T>
std::string GetTypeName() {
  // Step 1: Get compiler-encoded type name (e.g. "i" for int)
  const char* raw_name = typeid(T).name();

  // Step 2: Attempt to demangle the name (e.g. "_Z1i" → "int")
  int status = 0;
  char* demangled = abi::__cxa_demangle(raw_name, nullptr, nullptr, &status);

  // Step 3: Return demangled name if successful, otherwise fallback
  std::string result = (0 == status && demangled) ? demangled : raw_name;

  // Step 4: Free demangler-allocated memory
  std::free(demangled);

  return result;
}

/**
 * @brief Debug macro that prints an expression, its value and type
 * @param expr Expression to evaluate (any type)
 *
 * Execution Flow:
 * 1. Safely evaluates the expression once and stores result
 * 2. Captures the expression's static type via decltype
 * 3. Outputs formatted: "expr = value | type: typename"
 *
 * @note Uses do-while(0) wrapper for macro safety
 * @warning May produce compiler-specific type strings
 *
 * Technical Implementation:
 * - Uses auto to guarantee single evaluation
 * - decltype captures exact type including references/qualifiers
 * - GetTypeName() provides platform-aware type strings
 */
#define PRINT_TYPE(expr)                                                  \
  do {                                                                    \
    auto value = (expr);                 /* Single evaluation */          \
    typedef decltype(value) T;           /* Type deduction */             \
    std::cout << #expr << " = " << value /* Expression and value */       \
              << " | type: " << GetTypeName<T>() << '\n'; /* Type info */ \
  } while (0)

#endif  // INCLUDE_PRINT_TYPE_H_