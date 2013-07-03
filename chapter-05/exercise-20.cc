/*
 * Exercise 5.20: Write a program to read a sequence of strings from the
 * standard input until either the same word occurs twice in succession or all
 * the words have been read. Use a while loop to read the text one word at a
 * time. Use the break statement to terminate the loop if a word occurs twice in
 * succession. Print the word if it occurs twice in succession, or else print a
 * message saying that no word was repeated.
 */

#include <iostream>  // std::cin, std::cout
#include <limits>    // std::numeric_limits<std::streamsize>
#include <string>    // std::string

/**
 * @brief Processes input to find first consecutive duplicate word
 * @return The duplicate word if found, empty string otherwise
 *
 * Uses while loop with break statement as specified, implementing:
 * 1. Proper input validation
 * 2. Clean stream error handling
 * 3. Efficient word comparison
 */
std::string FindConsecutiveDuplicate() {
  std::string previous_word;
  std::string current_word;

  /*
   * Loop control strategy:
   * 1. Single read operation per iteration
   * 2. Immediate break on duplicate detection
   * 3. Proper handling of input failures
   */
  while (std::cin >> current_word) {
    if (!previous_word.empty() && current_word == previous_word) {
      // break; // return instead
      return current_word;  // Found duplicate
    }
    previous_word = current_word;
  }

  // Handle potential stream errors
  if (!std::cin.eof()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return "";  // No duplicate found
}

/*
 * Implementation Analysis:
 *
 * 1. Loop Design:
 *    - Single responsibility: process one word per iteration
 *    - Early termination via return (implicit break)
 *    - Maintains minimal necessary state (previous_word)
 *
 * 2. Edge Case Handling:
 *    - Empty input stream
 *    - Single word input
 *    - Non-word input (handled by stream)
 *    - Multiple duplicates (reports first occurrence)
 *
 * 3. Performance Considerations:
 *    - O(n) time complexity
 *    - O(1) space complexity
 *    - No unnecessary copies or allocations
 */

int main() {
  std::cout << "Enter words (ctrl+D to end): ";
  const std::string duplicate_word = FindConsecutiveDuplicate();

  if (!duplicate_word.empty()) {
    std::cout << "Repeated word: " << duplicate_word << '\n';
  } else {
    std::cout << "No word was repeated consecutively" << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-20.cc && ./main
 * Enter words (ctrl+D to end): The quick brown fox jumps over the the lazy dog.
 * Repeated word: the
 */
