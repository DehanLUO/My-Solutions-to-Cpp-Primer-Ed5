/*
 * Exercise 14.39: Revise the previous program to report the count of words that
 * are sizes 1 through 9 and 10 or more.
 */

#include <algorithm>  // std::count_if
#include <cstddef>    // std::size_t
#include <iostream>   // std::cin, std::cout
#include <string>     // std::string
#include <vector>     // std::vector

class LengthBoundChecker {
 public:
  /**
   * @brief Constructs a LengthBoundChecker with specified length bounds
   * @param min_length Minimum inclusive length bound
   * @param max_length Maximum inclusive length bound
   */
  explicit LengthBoundChecker(std::size_t min_length, std::size_t max_length)
      : min_length_(min_length), max_length_(max_length) {}

  /**
   * @brief Function call operator that performs length bound checking
   * @param str The string to check
   * @return bool True if string length is within bounds, false otherwise
   * @time Complexity O(1) - constant time string length check
   * @space Complexity O(1) - no additional space required
   */
  bool operator()(const std::string& str) const {
    const auto length = str.length();
    return length >= min_length_ && length <= max_length_;
  }

 private:
  std::size_t min_length_;  // Minimum inclusive length bound
  std::size_t max_length_;  // Maximum inclusive length bound
};

int main() {
  /*
   * Display instructions to the user about the input process.
   * The program will read words until end-of-file is encountered.
   */
  std::cout
      << "Enter text (words separated by whitespace, Ctrl+D/Ctrl+Z to end):\n";

  std::vector<std::string> vec;

  {
    std::string word;
    while (std::cin >> word) vec.push_back(word);
  }

  LengthBoundChecker checker(1, 9);
  auto count = std::count_if(vec.begin(), vec.end(), checker);
  std::cout << "len 1-9: " << count << '\n'  //
            << "len >= 10: " << vec.size() - count << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-39.cc && ./main
 * Enter text (words separated by whitespace, Ctrl+D/Ctrl+Z to end):
 * len 1-9: 10
 * len >= 10: 0
 */
