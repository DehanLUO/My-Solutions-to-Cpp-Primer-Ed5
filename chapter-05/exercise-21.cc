/*
 * Exercise 5.21: Revise the program from the exercise in § 5.5.1 (p. 191) so
 * that it looks only for duplicated words that start with an uppercase letter.
 */

/*
 * Exercise 5.21 Solution
 * Detects consecutive duplicate words that start with uppercase letters
 */

#include <cctype>    // isupper()
#include <iostream>  // std::cin, std::cout
#include <limits>    // std::numeric_limits<std::streamsize>
#include <string>    // std::string

/**
 * @brief Checks if a word starts with an uppercase letter
 * @param word The string to check
 * @return true if first character is uppercase, false otherwise
 *
 * Handles empty strings safely and demonstrates proper
 * character classification usage.
 */
bool StartsWithUppercase(const std::string& word) {
  if (word.empty()) return false;
  return isupper(static_cast<unsigned char>(word[0]));
}

/**
 * @brief Processes input to find first consecutive uppercase duplicate word
 * @return The duplicate word if found, empty string otherwise
 *
 * Implements modified duplicate detection with additional
 * uppercase requirement while maintaining all original
 * input handling robustness.
 */
std::string FindUppercaseConsecutiveDuplicate() {
  std::string previous_word;
  std::string current_word;

  /*
   * Modified detection logic:
   * 1. Only considers words starting with uppercase
   * 2. Maintains all original input validation
   * 3. Still efficient single-pass operation
   */
  while (std::cin >> current_word) {
    if (!previous_word.empty() && current_word == previous_word &&
        StartsWithUppercase(current_word)) {
      return current_word;
    }
    previous_word = current_word;
    // continue;  // Redundant continue statement at the end of loop statement
  }

  // Maintain original stream cleanup
  if (!std::cin.eof()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return "";
}

/*
 * Enhanced Implementation Analysis:
 *
 * 1. Uppercase Detection:
 *    - Uses standard library isupper()
 *    - Proper unsigned char casting
 *    - Empty string safety check
 *
 * 2. Modified Algorithm:
 *    - Adds minimal additional check
 *    - Maintains O(n) time complexity
 *    - Still O(1) space complexity
 *
 * 3. Behavioral Changes:
 *    - Now ignores lowercase duplicates
 *    - Still reports first qualifying duplicate
 *    - Same robust input handling
 */

int main() {
  std::cout << "Enter words (ctrl+D to end): ";
  const std::string duplicate_word = FindUppercaseConsecutiveDuplicate();

  if (!duplicate_word.empty()) {
    std::cout << "Repeated uppercase word: " << duplicate_word << '\n';
  } else {
    std::cout << "No uppercase word was repeated consecutively" << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-21.cc && ./main
 * Enter words (ctrl+D to end): The quick brown fox Fox Fox jumps over the lazy
 * dog. Repeated uppercase word: Fox
 */
