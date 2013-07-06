/*
 * Exercise 10.39: What kind of iterator does a list have? What about a vector?
 */

/*
 * Standard Container Iterator Categories:
 *
 * std::list iterator type:
 * - Category: BidirectionalIterator
 * - Supports: ++, --, *, ->, ==, !=
 * - Does NOT support: +, -, +=, -=, <, > (random access)
 *
 * std::vector iterator type:
 * - Category: RandomAccessIterator
 * - Supports all bidirectional operations PLUS:
 *   +, -, +=, -=, <, >, <=, >=, []
 * - Can jump to arbitrary positions
 */

#include <iterator>  // std::iterator_traits
#include <list>      // std:list
#include <vector>    // std::vector

int main() {
  // Compile-time verification
  static_assert(std::is_same<typename std::iterator_traits<
                                 std::list<int>::iterator>::iterator_category,
                             std::bidirectional_iterator_tag>::value,
                "list should have bidirectional iterators");

  static_assert(std::is_same<typename std::iterator_traits<
                                 std::vector<int>::iterator>::iterator_category,
                             std::random_access_iterator_tag>::value,
                "vector should have random access iterators");

  return 0;
}
