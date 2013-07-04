/*
 * Exercise 6.20: When should reference parameters be references to const? What
 * happens if we make a parameter a plain reference when it could be a reference
 * to const?
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Good example: const reference parameter
 * @param s Input string to examine (won't be modified)
 *
 * Use const reference when:
 * 1. You only need to read the parameter
 * 2. The object is expensive to copy
 * 3. You want to accept temporaries/rvalues
 */
void PrintString(const std::string& s) { std::cout << s << '\n'; }

/**
 * @brief Problematic example: non-const reference when const would suffice
 * @param s Input string (unnecessarily modifiable)
 *
 * Problems this causes:
 * 1. Can't pass const objects
 * 2. Can't pass string literals
 * 3. Can't pass temporaries
 * 4. Misleads callers about your intentions
 */
void PrintStringBad(std::string& s) {
  std::cout << s << '\n';  // Doesn't actually modify s
}

/*
 * Key Guidelines:
 *
 * 1. Use const references when:
 *    - You only need to observe the value
 *    - The parameter is large/expensive to copy
 *    - You want to accept rvalues/temporaries
 *
 * 2. Use plain references only when:
 *    - You need to modify the argument
 *    - The parameter is an "out" or "in-out" parameter
 *
 * 3. Consequences of unnecessary non-const references:
 *    - Limits what arguments can be passed
 *    - Miscommunicates function's intentions
 *    - May require callers to make unnecessary copies
 */

int main() {
  std::string hello = "Hello";
  const std::string world = "World";

  // Works with all cases:
  PrintString(hello);        // modifiable lvalue
  PrintString(world);        // const lvalue
  PrintString("Temporary");  // rvalue

  // Limited cases:
  PrintStringBad(hello);  // only works with modifiable lvalues
  // PrintStringBad(world);  // error: cannot bind const to non-const
  // PrintStringBad("Temp"); // error: cannot bind temporary

  return 0;
}

/* $ g++ -o main chapter-06/exercise-20.cc && ./main
 * Hello
 * World
 * Temporary
 * Hello
 */
