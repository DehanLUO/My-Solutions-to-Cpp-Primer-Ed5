/*
 * Exercise 6.44: Rewrite the isShorter function from § 6.2.2 (p. 211) to be
 * inline.
 *     // compare the length of two strings
 *     bool isShorter(const string &s1, const string &s2) {
 *       return s1.size() < s2.size();
 *     }
 */

#include <ios>       // std::boolalpha
#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Compares the length of two strings
 * @param s1 First string to compare
 * @param s2 Second string to compare
 * @return true if s1 is shorter than s2, false otherwise
 *
 * Demonstrates proper inline function implementation for a simple comparison.
 * The function is a good candidate for inlining due to its simplicity.
 */
inline bool IsShorter(const std::string& s1, const std::string& s2) {
  /*
   * Implementation notes:
   * 1. Marked inline to suggest inlining to compiler
   * 2. Uses const references to avoid copying
   * 3. Single expression fits inline function criteria
   */
  return s1.size() < s2.size();
}

int main() {
  // Test cases demonstrating inline function usage
  const std::string short_str = "short";
  const std::string long_str = "much longer string";

  std::cout << std::boolalpha;

  // Test 1: First string shorter
  std::cout << IsShorter(short_str, long_str) << '\n';  // Expected: true

  // Test 2: Second string shorter
  std::cout << IsShorter(long_str, short_str) << '\n';  // Expected: false

  // Test 3: Equal length strings
  std::cout << IsShorter(short_str, short_str) << '\n';  // Expected: false

  // Note: In real usage, these would be used in control flow
  // rather than stored in variables, demonstrating the benefit
  // of inlining for such simple operations

  return 0;
}

/* $ g++ -o main chapter-06/exercise-44.cc && ./main
 * true
 * false
 * false
 */
