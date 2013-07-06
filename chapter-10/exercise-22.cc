/*
 * Exercise 10.22: Rewrite the program to count words of size 6 or less using
 * functions in place of the lambdas.
 */

#include <algorithm>   // std::count_if
#include <functional>  // std::bind
#include <iostream>    // std::cout
#include <string>      // std::string
#include <vector>      // std::vector

/**
 * @brief Predicate function to check if string length is <= given size
 * @param s The string to check
 * @param max_len The maximum length to compare against
 * @return True if length <= max_len, false otherwise
 */
bool IsWithinLengthLimit(const std::string& s, size_t max_len) {
  return s.size() <= max_len;
}

/**
 * @brief Counts and prints words within specified length limit
 * @param words The vector of strings to process
 * @param sz Maximum allowed word length
 */
void CountLongWords(const std::vector<std::string>& words,
                    std::vector<std::string>::size_type sz) {
  // Count words with length <= sz
  auto count =
      std::count_if(words.begin(), words.end(),
                    std::bind(IsWithinLengthLimit, std::placeholders::_1, sz));

  // Format and print results
  std::cout << count << " word" << (count != 1 ? "s" : "") << " of length "
            << sz << " or less found:\n";

  // Print matching words
  for (const auto& word : words) {
    if (word.size() <= sz) {
      std::cout << " - " << word << '\n';
    }
  }
  std::cout << '\n';
}

int main() {
  std::vector<std::string> words = {"programming", "in",        "modern",
                                    "C++",         "is",        "powerful",
                                    "and",         "expressive"};

  // Test with different length thresholds
  CountLongWords(words, 5);  // Count words <= 5 characters
  CountLongWords(words, 3);  // Count words <= 3 characters
  CountLongWords(words, 6);  // Count words <= 6 characters

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-22.cc && ./main
 * 4 words of length 5 or less found:
 *  - in
 *  - C++
 *  - is
 *  - and
 *
 * 4 words of length 3 or less found:
 *  - in
 *  - C++
 *  - is
 *  - and
 *
 * 5 words of length 6 or less found:
 *  - in
 *  - modern
 *  - C++
 *  - is
 *  - and
 *
 */
