/*
 * Exercise 10.37: Given a vector that has ten elements, copy the elements from
 * positions 3 through 7 in reverse order to a list.
 */

#include <algorithm>  // std::copy
#include <iostream>   // std::cout
#include <iterator>   // std::advance, std::back_inserter
#include <list>       // std::list
#include <vector>     // std::vector

int main() {
  // Initialize vector with 10 elements (0-9)
  std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> lst1;
  std::list<int> lst2;

  // Get iterators for positions 3 (inclusive) and 8 (exclusive)
  auto vec_begin = vec.begin();
  std::advance(vec_begin, 3);  // Points to element 3
  auto vec_end = vec.begin();
  std::advance(vec_end, 7);  // Points to element 7 (we want inclusive)
  ++vec_end;                 // Points to the element after 7

  // Copy elements [3,7] in reverse order to list
  std::copy(vec_begin, vec_end, std::front_inserter(lst1));

  // Create reverse iterators explicitly
  std::reverse_iterator<decltype(vec_begin)> rbegin(vec_end), rend(vec_begin);

  // Copy elements [3,7] in reverse order to list
  std::copy(rbegin, rend, std::back_inserter(lst2));

  // Print results
  std::cout << "Original vector: ";
  for (int n : vec) std::cout << n << ' ';
  std::cout << "\nCopied list 1(elements 3-7 reversed): ";
  for (int n : lst1) std::cout << n << ' ';
  std::cout << "\nCopied list 2(elements 3-7 reversed): ";
  for (int n : lst1) std::cout << n << ' ';
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-37.cc && ./main
 * Original vector: 0 1 2 3 4 5 6 7 8 9
 * Copied list 1(elements 3-7 reversed): 7 6 5 4 3
 * Copied list 2(elements 3-7 reversed): 7 6 5 4 3
 */
