/*
 * Exercise 11.27: What kinds of problems would you use count to solve? When
 * might you use find instead?
 */

#include <iostream>  // std::cout
#include <map>       // std::map
#include <set>       // std::multiset
#include <string>    // std::string

/**
 * @brief Demonstrates proper use cases for count vs find
 */
void DemonstrateCountVsFind() {
  /*
   * Case 1: std::map (unique keys)
   *
   * For containers with unique keys (map, set):
   * - count can only return 0 or 1
   * - find is generally preferred for existence checks
   */
  std::map<std::string, int> word_count;
  word_count["apple"] = 3;

  /*
   * When to use find:
   * - Need to access the element if it exists
   * - More efficient (stops after first match)
   */
  auto found = word_count.find("apple");
  if (found != word_count.end()) {
    found->second += 1;  // Direct access to element
  }

  /*
   * When to use count:
   * - Only need boolean existence check
   * - More expressive when checking for non-existence
   */
  if (word_count.count("banana") == 0) {
    word_count["banana"] = 1;  // More readable than find...end()
  }
}

/**
 * @brief Shows count's advantage with non-unique keys
 */
void DemonstrateMultiContainerUsage() {
  std::multiset<std::string> words;
  words.insert("apple");
  words.insert("apple");
  words.insert("banana");

  /*
   * count is essential here to get total occurrences:
   * - Returns 2 for "apple"
   * - Returns 1 for "banana"
   * - Returns 0 for non-existent keys
   */
  size_t apple_count = words.count("apple");
  std::cout << "Apple appears " << apple_count << " times\n";

  /*
   * find alone is insufficient here as it only returns the first matching
   * element when duplicates exist
   */
  auto range = words.equal_range("apple");
  size_t manual_count = std::distance(range.first, range.second);
}

/**
 * @brief Compares performance characteristics
 */
void AnalyzePerformanceCharacteristics() {
  /*
   * Performance considerations:
   *
   * For unique-key containers:
   * - find: O(log n), stops at first match
   * - count: O(log n), must check for duplicates
   *
   * For multi-containers:
   * - find: O(log n), finds first match
   * - count: O(log n + k), where k is count of matches
   *
   * Recommendation:
   * - Use find when you only need one element
   * - Use count when you need the exact count
   */
  std::multimap<int, std::string> lookup_table;
  // ... populate with data ...

  // Efficient single-element access:
  auto first_match = lookup_table.find(42);

  // Necessary for complete count:
  size_t total_matches = lookup_table.count(42);
}

int main() {
  DemonstrateCountVsFind();

  DemonstrateMultiContainerUsage();

  AnalyzePerformanceCharacteristics();

  return 0;
}
