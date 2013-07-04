/*
 * Exercise 6.36: Write the declaration for a function that returns a reference
 * to an array of ten strings, without using either a trailing return, decltype,
 * or a type alias.
 */

#include <string>  // std::string

/**
 * @brief Declaration of function returning reference to array of 10 strings
 *
 * The function returns a reference to an array of 10 strings without using:
 * - Trailing return syntax
 * - decltype
 * - Type aliases
 *
 * @return std::string (&)[10] Reference to array of 10 strings
 */
std::string (&FunctionReturningStringArrayReference())[10];

/*
 * Detailed Explanation:
 *
 * The declaration follows standard C++ syntax for returning references to
 * arrays:
 * 1. FunctionReturningStringArrayReference()
 *    - A function that can be called with no arguments
 * 2. &FunctionReturningStringArrayReference()
 *    - Taking the address of (or returning a reference from) that function call
 * 3. std::string (&FunctionReturningStringArrayReference())[10]
 *    - The reference obtained refers to an array of 10 std::string objects
 *
 * This maintains several advantages:
 * - Preserves the exact array size in the type system
 * - Allows direct modification of the referenced array
 * - Avoids array-to-pointer decay
 *
 * The syntax is verbose but explicit about the return type.
 * Alternative approaches using modern C++ features would be:
 * 1. auto Function() -> std::string(&)[10] (trailing return)
 * 2. using StringArray = std::string[10]; StringArray& Function() (alias)
 * 3. decltype(string_array)& Function() (decltype)
 */
