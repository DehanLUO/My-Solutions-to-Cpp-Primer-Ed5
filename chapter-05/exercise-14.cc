/*
 * Exercise 5.14: Write a program to read strings from standard input looking
 * for duplicated words. The program should find places in the input where one
 * word is followed immediately by itself. Keep track of the largest number of
 * times a single repetition occurs and which word is repeated. Print the
 * maximum number of duplicates, or else print a message saying that no word was
 * repeated. For example, if the input is
 *     how now now now brown cow cow
 * the output should indicate that the word now occurred three times.
 */

#include <iostream>  // std::cin, std::cout
#include <string>    // std::string
#include <utility>   // std::pair

/**
 * @brief Finds the most frequently duplicated consecutive word in input
 * @details Reads whitespace-separated words from stdin and analyzes consecutive
 * duplicates. Tracks the word with highest consecutive repetition count.
 * @return A pair containing:
 *         - first: the most duplicated word (empty string if none)
 *         - second: the count of repetitions (0 if none)
 */
std::pair<std::string, size_t> FindMaxConsecutiveDuplicate() {
  std::string current_word, previous_word;
  std::string max_dup_word;  // Tracks word with highest consecutive duplicates
  size_t current_count = 1;  // Current streak count (minimum 1 for any word)
  size_t max_count = 1;      // Highest streak count found

  /*
   * Processing logic:
   * 1. Compare each word with its predecessor
   * 2. Reset counters when words differ
   * 3. Update maximum tracking variables when new record found
   */
  while (std::cin >> current_word) {
    if (current_word == previous_word) {
      ++current_count;
      // Update maximum if current streak exceeds previous record
      if (current_count > max_count) {
        max_count = current_count;
        max_dup_word = current_word;
      }
    } else {
      current_count = 1;  // Reset for new word
    }
    previous_word = current_word;
  }

  /*
   * Edge case handling:
   * - maxCount > 1 indicates at least one duplicate pair
   * - Otherwise return sentinel values
   */
  if (max_count <= 1) {
    return {"", 0};
  }
  return {max_dup_word, max_count};
}

int main() {
  std::cout << "Enter words (Ctrl+D to end input):\n";
  const auto [word, count] = FindMaxConsecutiveDuplicate();

  /*
   * Output decision tree:
   * - Distinguish between no duplicates vs. found duplicates cases
   * - Note: maxCount is always >= 2 when word is not empty
   */
  if (count == 0) {
    std::cout << "No word was consecutively repeated.\n";
  } else {
    std::cout << "Word '" << word << "' occurred " << count
              << " times consecutively.\n";
  }

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-14.cc && ./main
 * Enter words (Ctrl+D to end input):
 * how now now now brown cow cow
 * Word 'now' occurred 3 times consecutively.
 */
