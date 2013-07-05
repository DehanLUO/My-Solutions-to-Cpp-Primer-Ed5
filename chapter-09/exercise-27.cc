/*
 * Exercise 9.27: Write a program to find and remove the odd-valued elements in
 * a forward_list<int>.
 */

#include <forward_list>  // std::forward_list
#include <iostream>      // std::cout

/**
 * @brief Removes all odd-valued elements from a forward_list
 * @param flst The forward_list to modify
 *
 * Demonstrates proper forward_list element erasure using:
 * - before_begin() for position tracking
 * - erase_after() for element removal
 * - Iterator safety maintenance
 */
void RemoveOddValues(std::forward_list<int>& flst) {
  /*
   * Maintain two iterators:
   * - prev: Position before current element
   * - curr: Current element being examined
   */
  auto prev = flst.before_begin();  // denotes element "off the start" of flst
  auto curr = flst.begin();         // denotes the first element in flst
  while (curr != flst.end()) {      // while there are still elements to process
    if (*curr % 2 == 1) {           // if the element is odd
      /*
       * Erase element after prev (which is curr)
       * Returns iterator to next element
       */
      curr = flst.erase_after(prev);  // erast it and move curr
                                      // prev remains valid and correct
    } else {
      /*
       * Advance both iterators
       * Must increment prev before curr to maintain relationship
       */
      prev = curr;  // move the iterators to denote the next
      ++curr;       // element and one before the next element
    }
  }
}

/**
 * @brief Prints the contents of a forward_list
 */
void PrintForwardList(const std::forward_list<int>& flst) {
  for (const int num : flst) {
    std::cout << num << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::cout << "Original list:\n";
  PrintForwardList(flst);

  RemoveOddValues(flst);

  std::cout << "After removing odd values:\n";
  PrintForwardList(flst);

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-27.cc && ./main
 * Original list:
 * 0 1 2 3 4 5 6 7 8 9
 * After removing odd values:
 * 0 2 4 6 8
 */
