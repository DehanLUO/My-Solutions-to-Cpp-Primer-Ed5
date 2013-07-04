/*
 * Exercise 6.29: When you use an initializer_list in a range for would you ever
 * use a reference as the loop control variable? If so, why? If not, why not?
 */

#include <initializer_list>  // std::initializer_list
#include <iostream>          // std::cout
#include <string>            // std::string

void ProcessValues(std::initializer_list<std::string> il) {
  // Case 1: Use reference when modifying or avoiding copies
  for (auto& s : il) {  // const auto& would be better here
    // s could be modified (but shouldn't for initializer_list!)
    std::cout << s << " ";
  }
  std::cout << '\n';

  // Case 2: Better practice - use const reference
  for (const auto& s : il) {
    // Read-only access, no copying
    std::cout << s << " ";
  }
  std::cout << '\n';

  // Case 3: Use value when you need a copy anyway
  for (auto s : il) {
    // Expensive copy for each string
    s += " (processed)";
    std::cout << s << " ";
  }
  std::cout << '\n';
}

/*
 * Key Guidelines:
 *
 * 1. Always prefer const auto& for initializer_list:
 *    - Avoids copying elements
 *    - Elements in initializer_list are already const
 *
 * 2. Never use non-const reference:
 *    - initializer_list elements are always const
 *    - Attempting to modify will cause compiler error
 *
 * 3. Only use by-value (auto) when:
 *    - You explicitly need modifiable copies
 *    - Dealing with primitive types (int, char, etc.)
 */

int main() {
  ProcessValues({"apple", "banana", "cherry"});

  /* Output:
   * apple banana cherry
   * apple banana cherry
   * apple (processed) banana (processed) cherry (processed)
   */
  return 0;
}

/* $ g++ -o main chapter-06/exercise-29.cc && ./main
 * apple banana cherry
 * apple banana cherry
 * apple (processed) banana (processed) cherry (processed)
 */
