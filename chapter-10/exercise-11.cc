/*
 * Exercise 10.11: Write a program that uses stable_sort and isShorter to sort a
 * vector passed to your version of elimDups. Print the vector to verify that
 * your program is correct.
 */

#include <algorithm>  // std::sort, std::unique, std::stable_sort
#include <iostream>   // std::cout
#include <string>     // std::string
#include <vector>     // std::vector

/**
 * @brief Predicate to compare string lengths
 * @param a First string to compare
 * @param b Second string to compare
 * @return True if a is shorter than b
 */
bool IsShorter(const std::string& a, const std::string& b) {
  return a.length() < b.length();
}

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
 * @brief Removes duplicates and sorts by length while preserving relative order
 * @param words The vector to process (will be modified)
 *
 * Operation sequence:
 * 1. Sort alphabetically
 * 2. Eliminate duplicates
 * 3. Stable sort by length
 */
void EliminateDuplicatesAndSortByLength(std::vector<std::string>& words) {
  /* Initial state */
  PrintVectorState(words, "Original input");

  /* Phase 1: Sort alphabetically */
  std::sort(words.begin(), words.end());
  PrintVectorState(words, "After alphabetical sort");

  /* Phase 2: Eliminate duplicates */
  const auto end_unique = std::unique(words.begin(), words.end());
  words.erase(end_unique, words.end());
  PrintVectorState(words, "After removing duplicates");

  /*
   * Phase 3: Stable sort by length
   * Maintains relative order of equal-length elements
   */
  std::stable_sort(words.begin(), words.end(), IsShorter);
  PrintVectorState(words, "After stable_sort by length");
}

int main() {
  /* Case 1: Mixed lengths with potential duplicates */
  std::vector<std::string> test_case = {"apple", "zebra", "banana", "pineapple",
                                        "kiwi",  "apple", "grape"};

  std::cout << "=== TEST CASE 1 ===\n";
  EliminateDuplicatesAndSortByLength(test_case);

  /* Case 2: All same length */
  std::vector<std::string> same_length_case = {"dog", "cat", "bat", "rat",
                                               "hat"};

  std::cout << "\n=== TEST CASE 2 ===\n";
  EliminateDuplicatesAndSortByLength(same_length_case);

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-11.cc && ./main
 * === TEST CASE 1 ===
 * --- Original input ---
 * apple zebra banana pineapple kiwi apple grape
 *
 * --- After alphabetical sort ---
 * apple apple banana grape kiwi pineapple zebra
 *
 * --- After removing duplicates ---
 * apple banana grape kiwi pineapple zebra
 *
 * --- After stable_sort by length ---
 * kiwi apple grape zebra banana pineapple
 *
 *
 * === TEST CASE 2 ===
 * --- Original input ---
 * dog cat bat rat hat
 *
 * --- After alphabetical sort ---
 * bat cat dog hat rat
 *
 * --- After removing duplicates ---
 * bat cat dog hat rat
 *
 * --- After stable_sort by length ---
 * bat cat dog hat rat
 *
 */
