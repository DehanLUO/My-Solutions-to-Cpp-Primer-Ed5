/*
 * Exercise 14.38: Write a class that tests whether the length of a given string
 * matches a given bound. Use that object to write a program to report how many
 * words in an input file are of sizes 1 through 10 inclusive.
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

  for (int length = 1; length <= 10; ++length) {
    LengthBoundChecker checker(length, length);
    std::cout << "len: " << length
              << ", cnt: " << std::count_if(vec.begin(), vec.end(), checker)
              << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-38.cc && ./main < data/count-size
 * Enter text (words separated by whitespace, Ctrl+D/Ctrl+Z to end):
 * len: 1, cnt: 0
 * len: 2, cnt: 0
 * len: 3, cnt: 5
 * len: 4, cnt: 2
 * len: 5, cnt: 2
 * len: 6, cnt: 1
 * len: 7, cnt: 0
 * len: 8, cnt: 0
 * len: 9, cnt: 0
 * len: 10, cnt: 0
 */
