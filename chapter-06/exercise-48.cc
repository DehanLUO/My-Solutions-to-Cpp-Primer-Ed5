/*
 * Exercise 6.48: Explain what this loop does and whether it is a good use of
 * assert:
 *     string s;
 *     while (cin >> s && s != sought) { } // empty body
 *     assert(cin);
 */

#include <cassert>   // assert
#include <iostream>  // std::cin
#include <string>    // std::string

/**
 * @brief Analyzes the given code snippet with assert
 *
 * Demonstrates proper use of assertions in input validation scenarios.
 * The original code checks for successful input operations but may misuse
 * assert.
 */
void AnalyzeAssertUsage() {
  /*
   * Original code analysis:
   * string s;
   * while (cin >> s && s != sought) { }
   * assert(cin);
   *
   * Purpose:
   * 1. Reads strings from input until 'sought' is found or input fails
   * 2. Asserts that the input stream is still valid
   */

  std::string sought = "target";
  std::string s;

  // Better implementation alternative:
  while (std::cin >> s && s != sought) {
    // Empty body is acceptable for search loops
  }

  /* Assertion critique:
   * 1. Wrong use case - assert is for debugging logic errors, not input
   * validation
   * 2. Input failure is normal runtime behavior, not a programming error
   * 3. assert disappears in production (NDEBUG defined)
   *
   * Better approach would be explicit error checking:
   */
  if (!std::cin) {
    std::cerr << "Input error or end-of-file reached\n";
  }
}

int main() {
  AnalyzeAssertUsage();  // Demonstrate the analysis

  return 0;
}

/* $ g++ -o main chapter-06/exercise-48.cc && ./main
 * Input error or end-of-file reached
 */
