/*
 * Exercise 9.21: Explain how the loop from page 345 that used the return from
 * insert to add elements to a list would work if we inserted into a vector
 * instead.
 *     list<string> lst;
 *     auto iter = lst.begin();
 *     while (cin >> word)
 *       iter = lst.insert(iter, word); // same as calling push_front
 */

#include <iostream>  // std::cin, std::cout
#include <list>      // std::list
#include <string>    // std::string
#include <vector>    // std::vector

/**
 * @brief Demonstrates insertion behavior differences between list and vector
 *
 * Shows the critical differences when using insert() with:
 * 1. std::list (original example)
 * 2. std::vector (modified version)
 */
void DemonstrateInsertBehavior() {
  /* Original list version (efficient) */
  std::list<std::string> lst;
  auto list_iter = lst.begin();

  /*
   * List insertion characteristics:
   * - O(1) time complexity per insertion
   * - No reallocation needed
   * - Iterators remain valid after insertion
   * - Effectively builds list in reverse order
   */
  std::string word;
  while (std::cin >> word) {
    list_iter = lst.insert(list_iter, word);  // Always O(1)
  }

  /* Vector version (with performance implications) */
  std::vector<std::string> vec;
  auto vec_iter = vec.begin();

  /*
   * Vector insertion differences:
   * 1. Insertion at beginning is O(N) due to element shifting
   * 2. Reallocation may invalidate iterators
   * 3. Capacity management becomes crucial
   * 4. Much worse performance for large inputs
   */
  std::cin.clear();  // Reset stream state for second read
  while (std::cin >> word) {
    vec_iter = vec.insert(vec_iter, word);  // O(N) each time!

    /*
     * Critical: Must update iterator after each insert because:
     * - insert() may cause reallocation
     * - All iterators before insertion point remain valid
     * - But we're inserting at beginning, so all iterators invalidate
     */
    vec_iter = vec.begin();  //! Must reset iterator
  }
}

/**
 * @brief Better approach for vector insertion
 * Demonstrates proper way to prepend to vector
 */
void EfficientVectorInsert() {
  std::vector<std::string> vec;
  std::string word;

  /*
   * Preferred method for vector prepending:
   * 1. Read all input first
   * 2. Insert in reverse order
   * 3. Or use std::deque if frequent front insertion needed
   */
  while (std::cin >> word) {
    vec.push_back(word);  // O(1) amortized
  }

  // Reverse after collection if needed
  std::reverse(vec.begin(), vec.end());
}

int main() {
  /*
   * Execution notes:
   * - Run one demonstration at a time
   * - Use small input sets for vector demonstration
   * - Ctrl+D (Unix) or Ctrl+Z (Windows) to end input
   */
  // DemonstrateInsertBehavior();
  EfficientVectorInsert();

  return 0;
}
