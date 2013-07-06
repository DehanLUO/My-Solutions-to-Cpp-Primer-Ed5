/*
 * Exercise 10.9: Implement your own version of elimDups. Test your program by
 * printing the vector after you read the input, after the call to unique, and
 * after the call to erase.
 *     void elimDups(vector<string> &words) {
 *       // sort words alphabetically so we can find the duplicates
 *       sort(words.begin(), words.end());
 *       // unique reorders the input range so that each word appears once in
 *       // the front portion of the range and returns an iterator one past the
 *       // unique range
 *       auto end_unique = unique(words.begin(), words.end());
 *       // erase uses a vector operation to remove the nonunique elements
 *       words.erase(end_unique, words.end());
 *     }
 */

#include <algorithm>  // std::sort, std::unique
#include <iostream>   // std::cout
#include <iterator>   // std::distance
#include <string>     // std::string
#include <vector>     // std::vector

/**
 * @brief Prints vector contents with diagnostic label
 * @param words The vector to print
 * @param label Description of print state
 */
void PrintVectorState(const std::vector<std::string>& words,
                      const std::string& label) {
  std::cout << "--- " << label << " ---\n";
  for (const auto& word : words) {
    std::cout << word << ' ';
  }
  std::cout << "\n\n";
}

/**
 * @brief Removes duplicate strings from a vector while preserving order
 * @param words The vector to process (will be modified)
 *
 * Operation sequence:
 * 1. Sort to group duplicates
 * 2. Unique to collapse duplicates
 * 3. Erase to remove leftover elements
 */
void EliminateDuplicates(std::vector<std::string>& words) {
  /* Initial state before any processing */
  PrintVectorState(words, "Original input");

  /* Phase 1: Sort the vector alphabetically */
  std::sort(words.begin(), words.end());
  PrintVectorState(words, "After sorting");

  /*
   * Phase 2: Collapse adjacent duplicates
   * unique returns new logical end iterator
   */
  const auto new_end = std::unique(words.begin(), words.end());
  PrintVectorState(words, "After unique (physical state)");

  /*
   * Important Observation:
   * The physical container still contains extra elements after unique
   * They exist between new_end and words.end()
   */
  std::cout << "Logical unique range: [0, "
            << std::distance(words.begin(), new_end) << ")\n";

  /* Phase 3: Erase the non-unique elements */
  words.erase(new_end, words.end());
  PrintVectorState(words, "After erase");
}

int main() {
  /* Case 1: Typical input with duplicates */
  std::vector<std::string> test_case = {"apple", "orange", "banana",
                                        "apple", "grape",  "banana"};
  EliminateDuplicates(test_case);

  /* Case 2: Already unique */
  std::vector<std::string> unique_case = {"one", "two", "three"};
  EliminateDuplicates(unique_case);

  /* Case 3: All duplicates */
  std::vector<std::string> dup_case = {"same", "same", "same"};
  EliminateDuplicates(dup_case);

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-09.cc && ./main
 * --- Original input ---
 * apple orange banana apple grape banana
 *
 * --- After sorting ---
 * apple apple banana banana grape orange
 *
 * --- After unique (physical state) ---
 * apple banana grape orange
 *
 * Logical unique range: [0, 4)
 * --- After erase ---
 * apple banana grape orange
 *
 * --- Original input ---
 * one two three
 *
 * --- After sorting ---
 * one three two
 *
 * --- After unique (physical state) ---
 * one three two
 *
 * Logical unique range: [0, 3)
 * --- After erase ---
 * one three two
 *
 * --- Original input ---
 * same same same
 *
 * --- After sorting ---
 * same same same
 *
 * --- After unique (physical state) ---
 * same same same
 *
 * Logical unique range: [0, 1)
 * --- After erase ---
 * same
 *
 */
