/*
 * Exercise 9.31: The program on page 354 to remove even-valued elements and
 * duplicate odd ones will not work on a list or forward_list. Why? Revise the
 * program so that it works on these types as well.
 *     // silly loop to remove even-valued elements and insert a duplicate of
 *     // odd-valued elements
 *     std::vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
 *     auto iter = vi.begin();  // call begin, not cbegin because we are
 *                              // changing vi
 *     while (iter != vi.end()) {
 *       if (*iter % 2) {
 *         iter = vi.insert(iter, *iter);  // duplicate the current element
 *         iter += 2;  // advance post this element
 *                     // and the one inserted before it
 *       } else {
 *         iter = vi.erase(iter);  // remove even elements
 *         // don't advance the iterator;
 *         // iter denotes the element after the one we erased
 *       }
 *     }
 */

#include <cassert>       // std::begin, std::end
#include <forward_list>  // std::forward_list
#include <iostream>      // std::cout
#include <list>          // std::list

/**
 * @brief Processes a list by duplicating odd numbers and removing even numbers
 * @param lst The list to process
 *
 * For each odd number, inserts a duplicate before it
 * Removes all even numbers
 */
void ProcessList(std::list<int>& lst) {
  auto iter = lst.begin();
  while (iter != lst.end()) {
    if (1 == *iter % 2) {              // if odd
      iter = lst.insert(iter, *iter);  // insert copy before current
      ++iter;                          // skip original
      ++iter;                          // move to next element
    } else {
      iter = lst.erase(iter);  // erase even element
    }
  }
}

/**
 * @brief Processes a forward_list by duplicating odd numbers and removing even
 * numbers
 * @param flst The forward_list to process
 *
 * Uses before_begin() and insert_after/erase_after since forward_list
 * doesn't support direct insertion/deletion at current position
 */
void ProcessForwardList(std::forward_list<int>& flst) {
  auto prev = flst.before_begin();
  auto curr = flst.begin();

  while (curr != flst.end()) {
    if (1 == *curr % 2) {
      curr = flst.insert_after(curr, *curr);  // Insert copy after current
      prev = curr;                            // Update previous position
      ++curr;                                 // Move to next element
    } else {
      curr = flst.erase_after(prev);
    }
  }
}

int main() {
  int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::list<int> lst(std::begin(array), std::end(array));
  ProcessList(lst);

  for (int num : lst) std::cout << num << ' ';
  std::cout << '\n';

  std::forward_list<int> flst(std::begin(array), std::end(array));
  ProcessForwardList(flst);

  for (int num : flst) std::cout << num << ' ';
  // Output: 1 1 3 3 5 5 7 7 9 9

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-31.cc && ./main
 * 1 1 3 3 5 5 7 7 9 9
 * 1 1 3 3 5 5 7 7 9 9
 */
