/*
 * Exercise 9.25: In the program on page 349 that erased a range of elements,
 * what happens if elem1 and elem2 are equal? What if elem2 or both elem1 and
 * elem2 are the off-the-end iterator?
 *     // delete the range of elements between two iterators
 *     // returns an iterator to the element just after the last removed element
 *     elem1 = slist.erase(elem1, elem2); // after the call elem1 == elem2
 */

#include <iostream>  // std::cout
#include <list>      // std::list

/**
 * @brief Demonstrates edge cases for list::erase() with iterators
 *
 * Tests three special cases:
 * 1. elem1 == elem2 (equal iterators)
 * 2. elem2 is end()
 * 3. Both iterators are end()
 */
void TestEraseEdgeCases() {
  // Original list for testing
  std::list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  /* Case 1: Equal iterators (erase empty range) */
  auto it1 = lst.begin();
  std::advance(it1, 3);  // Points to 3
  auto it2 = it1;

  /*
   * Behavior: Erases nothing (range [it1, it2) is empty)
   * Returns: it2 (unchanged)
   * Valid operation, no elements removed
   */
  auto result1 = lst.erase(it1, it2);
  std::cout << "After equal iterators erase, size: " << lst.size() << '\n';
  std::cout << "Returned iterator points to: " << *result1 << '\n';

  /* Case 2: elem2 is end() */
  auto it3 = lst.begin();
  std::advance(it3, 7);  // Points to 7
  auto it4 = lst.end();

  /*
   * Behavior: Erases from it3 to end (7, 8, 9)
   * Returns: end()
   * Valid operation, removes tail elements
   */
  auto result2 = lst.erase(it3, it4);
  std::cout << "After end() as elem2, size: " << lst.size() << '\n';
  std::cout << "Returned iterator is end(): " << (result2 == lst.end()) << '\n';

  /* Case 3: Both iterators are end() */
  auto it5 = lst.end();
  auto it6 = lst.end();

  /*
   * Behavior: Erases nothing (empty range at end)
   * Returns: end()
   * Valid operation, no elements removed
   */
  auto result3 = lst.erase(it5, it6);
  std::cout << "After both end() iterators, size: " << lst.size() << '\n';
  std::cout << "Returned iterator is end(): " << (result3 == lst.end()) << '\n';
}

int main() {
  // Edge case testing
  TestEraseEdgeCases();

  return 0;
}
/*
 * $ g++ -o main chapter-09/exercise-25.cc && ./main
 * After equal iterators erase, size: 10
 * Returned iterator points to: 3
 * After end() as elem2, size: 7
 * Returned iterator is end(): 1
 * After both end() iterators, size: 7
 * Returned iterator is end(): 1
 */
