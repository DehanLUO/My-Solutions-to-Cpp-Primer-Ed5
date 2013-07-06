/*
 * Exercise 10.41: Based only on the algorithm and argument names, describe the
 * operation that the each of the following library algorithms performs:
 *     replace(beg, end, old_val, new_val);
 *     replace_if(beg, end, pred, new_val);
 *     replace_copy(beg, end, dest, old_val, new_val);
 *     replace_copy_if(beg, end, dest, pred, new_val);
 */

/*
 * Replace Algorithm Family:
 *
 * 1. replace(beg, end, old_val, new_val):
 *    - Replaces ALL occurrences of 'old_val' with 'new_val'
 *    - Modifies the original range in-place
 *    - Example: replace all 5s with 10
 *
 * 2. replace_if(beg, end, pred, new_val):
 *    - Replaces elements where pred(element) is true
 *    - Modifies in-place
 *    - Example: replace all even numbers with 0
 *
 * 3. replace_copy(beg, end, dest, old_val, new_val):
 *    - Copies range to 'dest', replacing 'old_val' with 'new_val'
 *    - Preserves original range
 *    - Example: copy vector, replacing 5s with 10s
 *
 * 4. replace_copy_if(beg, end, dest, pred, new_val):
 *    - Copies range to 'dest', replacing when pred(element) is true
 *    - Preserves original range
 *    - Example: copy vector, replacing negatives with 0
 */

#include <algorithm>  // std::replace, std::replace_if, std::replace_copy
#include <iostream>   // std::cout
#include <vector>     // std::vector

int main() {
  // Practical examples
  std::vector<int> vec = {1, 2, 3, 2, 5};
  std::vector<int> out;

  // 1. Basic replace
  std::replace(vec.begin(), vec.end(), 2, 20);
  std::cout << "\nAfter replace: ";
  for (int n : vec) std::cout << n << ' ';

  // 2. Conditional replace
  std::replace_if(vec.begin(), vec.end(), [](int n) { return n > 3; }, 0);
  std::cout << "\nAfter replace_if: ";
  for (int n : vec) std::cout << n << ' ';

  // 3. Copying replace
  vec = {1, 2, 3, 2, 5};
  out.resize(vec.size());
  std::replace_copy(vec.begin(), vec.end(), out.begin(), 2, 20);
  std::cout << "After replace_copy (original unchanged): ";
  for (int n : vec) std::cout << n << ' ';
  std::cout << "\nOutput contains: ";
  for (int n : out) std::cout << n << ' ';

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-41.cc && ./main
 * After replace: 1 20 3 20 5
 * After replace_if: 1 0 3 0 0
 * After replace_copy (original unchanged): 1 2 3 2 5
 * Output contains: 1 20 3 20 5
 */
