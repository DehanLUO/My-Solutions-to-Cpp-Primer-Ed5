// Exercise 9.6: What is wrong with the following program? How might you correct
// it?
//     list<int> lst1; list<int>::iterator iter1 = lst1.begin(),
//                                         iter2 = lst1.end();
//     while (iter1 < iter2) /* ... */

#include <list>  // std::list

/*
 * Original issue:
 * - Used invalid operator< for list iterators
 * - Bidirectional iterators only support equality comparison (==, !=)
 *
 * Correct approach:
 * - Use != for iterator comparison
 * - Works for all iterator categories
 *
 * Iterator category comparison support
 *
 * | Operation | Input | Forward | Bidirectional | Random Access |
 * |-----------|-------|---------|---------------|---------------|
 * | ==, !=    | Yes   | Yes     | Yes           | Yes           |
 * | <, >      | No    | No      | No            | Yes           |
 * | <=, >=    | No    | No      | No            | Yes           |
 */

int main() {
  std::list<int> lst1;
  std::list<int>::iterator iter1 = lst1.begin();
  std::list<int>::iterator iter2 = lst1.end();

  // Corrected comparison
  while (iter1 != iter2) {  // Valid for all iterator types
    // ... process elements
    ++iter1;
  }

  return 0;
}
