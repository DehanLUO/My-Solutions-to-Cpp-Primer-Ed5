/*
 * Exercise 11.29: What do upper_bound, lower_bound, and equal_range return when
 * you pass them a key that is not in the container?
 */

#include <map>     // std::map
#include <string>  // std::string

/**
 * @brief Demonstrates bound operations on missing keys
 */
void DemonstrateBoundsOnMissingKeys() {
  std::map<int, std::string> test_map = {
      {10, "ten"}, {20, "twenty"}, {30, "thirty"}, {40, "forty"}};

  /*
   * Case 1: Key below all existing keys (5)
   *
   * All operations return begin() because:
   * - 5 would be inserted at the first position
   */
  auto lb1 = test_map.lower_bound(5);
  auto ub1 = test_map.upper_bound(5);
  auto er1 = test_map.equal_range(5);

  /*
   * Case 2: Key between existing keys (25)
   *
   * Returns insertion point between elements:
   * - lower_bound: first element >= 25 → 30
   * - upper_bound: first element > 25 → 30 (same in this case)
   * - equal_range: both bounds point to 30
   */
  auto lb2 = test_map.lower_bound(25);
  auto ub2 = test_map.upper_bound(25);
  auto er2 = test_map.equal_range(25);

  /*
   * Case 3: Key above all existing keys (50)
   *
   * All operations return end() because:
   * - 50 would be inserted at the end
   */
  auto lb3 = test_map.lower_bound(50);
  auto ub3 = test_map.upper_bound(50);
  auto er3 = test_map.equal_range(50);
}

/**
 * @brief Shows practical implications for insertion
 */
void DemonstrateInsertionUsage() {
  std::map<std::string, int> word_map = {
      {"apple", 1}, {"cherry", 3}, {"date", 4}};

  /*
   * Using lower_bound to find insertion point:
   * - For existing key: returns existing element
   * - For missing key: returns where it should be
   */
  auto insert_pos = word_map.lower_bound("banana");

  /*
   * This allows efficient insertion while:
   * 1. Maintaining sort order
   * 2. Avoiding duplicate keys
   */
  if (insert_pos == word_map.end() || insert_pos->first != "banana") {
    word_map.insert(insert_pos, {"banana", 2});
  }
}

/**
 * @brief Compares behaviors across container types
 */
void CompareContainerBehaviors() {
  /*
   * In std::map (unique keys):
   * - equal_range returns [lower, upper) where:
   *   - lower == upper for missing keys
   *   - lower == position where key would be
   */
  std::map<int, int> unique_map;
  auto unique_range = unique_map.equal_range(10);

  /*
   * In std::multimap (duplicate keys):
   * - Same behavior for missing keys
   * - For existing keys, range spans all duplicates
   */
  std::multimap<int, int> multi_map;
  auto multi_range = multi_map.equal_range(10);
}

int main() {
  DemonstrateBoundsOnMissingKeys();
  DemonstrateInsertionUsage();
  CompareContainerBehaviors();
  return 0;
}
