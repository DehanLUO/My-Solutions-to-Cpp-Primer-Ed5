/*
 * Exercise 6.46: Would it be possible to define isShorter as a constexpr? If
 * so, do so. If not, explain why not.
 */

#include <cassert>   // static_assert
#include <ios>       // std::boolalpha
#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Compares the length of two strings
 * @param s1 First string to compare
 * @param s2 Second string to compare
 * @return true if s1 is shorter than s2, false otherwise
 *
 * Cannot be constexpr because:
 * 1. std::string operations aren't constexpr in C++11
 * 2. String comparison involves non-constexpr operations
 * 3. std::string constructor isn't constexpr
 */
bool IsShorter(const std::string& s1, const std::string& s2) {
  return s1.size() < s2.size();
}

/**
 * @brief Alternative compile-time comparison
 * @tparam N1 Length of first string literal
 * @tparam N2 Length of second string literal
 * @param s1 First string literal
 * @param s2 Second string literal
 * @return true if s1 is shorter than s2
 */
template <size_t N1, size_t N2>
constexpr bool IsShorterCompileTime(const char (&s1)[N1],
                                    const char (&s2)[N2]) {
  return N1 - 1 < N2 - 1;  // -1 to exclude null terminator
}

int main() {
  std::cout << std::boolalpha;

  // Runtime version (works with std::string)
  std::string a = "apple";
  std::string b = "banana";
  std::cout << IsShorter(a, b) << '\n';  // true

  // Compile-time version (only works with string literals)
  static_assert(IsShorterCompileTime("apple", "banana"), "Test failed");
  static_assert(!IsShorterCompileTime("banana", "apple"), "Test failed");

  return 0;
}

/* $ g++ -o main chapter-06/exercise-46.cc && ./main
 * true
 */
