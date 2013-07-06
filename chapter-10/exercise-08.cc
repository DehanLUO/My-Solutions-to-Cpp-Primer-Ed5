/*
 * Exercise 10.8: We said that algorithms do not change the size of the
 * containers over which they operate. Why doesn’t the use of back_inserter
 * invalidate this claim?
 */

#include <algorithm>  // std::copy, std::fill_n
#include <iterator>   // std::back_inserter
#include <vector>     // std::vector

/*
 * Detailed explanation of the iterator adaptor's role.
 * Conceptual Model:
 * +---------------------+       +----------------+       +------------+
 * | Algorithm           | ----> | Iterator       | ----> | Container  |
 * | (e.g., copy)        |       | (back_inserter)|       | (vector)   |
 * | Doesn't know about  |       | Knows about    |       | Modified   |
 * | container growth    |       | container      |       | by iterator|
 * +---------------------+       +----------------+       +------------+
 *
 * Key Insight:
 * The algorithm remains container-agnostic - it's the iterator adaptor
 * that translates assignments into container operations.
 */

/*
 * Comparative example showing direct size modification vs iterator adaptation.
 */
void CompareModificationMethods() {
  std::vector<int> v1, v2;

  // Method that DOES violate the claim (hypothetical)
  // NOT actual STL code - for illustration only
  // v1.algorithms_resize_and_fill(10, 0);  // Doesn't exist

  // Proper STL method that maintains the claim
  std::fill_n(std::back_inserter(v2), 10, 0);  // Valid

  /*
   * Design Principle:
   * The STL maintains separation of concerns where:
   * - Algorithms operate on sequences via iterators
   * - Containers manage storage
   * - Iterators mediate access
   * back_inserter preserves this architecture while providing growth
   */
}

int main() {
  std::vector<int> source = {1, 2, 3};
  std::vector<int> destination;

  /*
   * Critical Analysis Point:
   * The copy algorithm itself doesn't modify the container size -
   * it simply performs assignments through iterators.
   * The growth happens through the back_inserter's operations.
   */
  std::copy(source.begin(), source.end(), std::back_inserter(destination));

  /*
   * Technical Breakdown:
   * 1. copy() only knows it's doing *dest++ = *source++
   * 2. back_inserter's operator= calls push_back()
   * 3. push_back() is part of the iterator's implementation
   */

  return 0;
}
