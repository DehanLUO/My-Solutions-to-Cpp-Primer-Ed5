/*
 * Exercise 10.7: Determine if there are any errors in the following programs
 * and, if so, correct the error(s):
 *     (a) vector<int> vec; list<int> lst; int i;
 *           while (cin >> i)
 *             lst.push_back(i);
 *           copy(lst.cbegin(), lst.cend(), vec.begin());
 *     (b) vector<int> vec;
 *         vec.reserve(10); // reserve is covered in § 9.4 (p. 356)
 *         fill_n(vec.begin(), 10, 0);
 */

#include <algorithm>  // std::copy, std::fill_n
#include <iostream>   // std::cin
#include <iterator>   // std::back_inserter
#include <list>       // std::list
#include <vector>     // std::vector

/*
 * Corrected version of program (a) demonstrating proper container copying.
 * Original issues:
 * 1. vec is empty - copy tries to write to non-existent elements
 * 2. No space allocated in destination vector
 */
void CorrectedProgramA() {
  std::vector<int> vec;
  std::list<int> lst;
  int i;

  // Read input into list
  while (std::cin >> i) {
    lst.push_back(i);
  }

  /*
   * Solution Approaches:
   * 1. Pre-size vector to match list size
   * 2. Use back_inserter to handle growth automatically
   *
   * Method 1 shown here, Method 2 shown in comments
   */
  vec.resize(lst.size());  // Required for direct copy
  std::copy(lst.cbegin(), lst.cend(), vec.begin());

  // Alternative method using back_inserter:
  // std::copy(lst.cbegin(), lst.cend(), std::back_inserter(vec));
}

/*
 * Corrected version of program (b) demonstrating proper container
 * initialization. Original issues:
 * 1. reserve() only allocates memory, doesn't create elements
 * 2. fill_n writes to non-existent elements
 */
void CorrectedProgramB() {
  std::vector<int> vec;

  /*
   * Critical Distinction:
   * reserve() vs resize():
   * - reserve: Allocates memory only (capacity)
   * - resize: Creates actual elements (size)
   */
  vec.resize(10);  // Creates 10 elements initialized to 0
  std::fill_n(vec.begin(), 10, 0);

  /*
   * Alternative Solutions:
   * 1. Constructor initialization: vector<int> vec(10, 0);
   * 2. push_back in loop (inefficient)
   * 3. insert with fill_n and back_inserter:
   *    fill_n(back_inserter(vec), 10, 0);
   */
}

int main() {
  /*
   * Program (a) Analysis:
   * 1. Empty vector has begin() == end()
   * 2. copy requires pre-allocated space
   * 3. Undefined behavior when writing past end()
   */
  CorrectedProgramA();

  /*
   * Program (b) Analysis:
   * 1. reserve() doesn't create accessible elements
   * 2. fill_n requires valid elements to overwrite
   * 3. Capacity != Size in vector semantics
   */
  CorrectedProgramB();

  return 0;
}
