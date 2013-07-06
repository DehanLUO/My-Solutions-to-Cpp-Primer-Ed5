/*
 * Exercise 10.27: In addition to unique (§ 10.2.3, p. 384), the library defines
 * function named unique_copy that takes a third iterator denoting a destination
 * into which to copy the unique elements. Write a program that uses unique_copy
 * to copy the unique elements from a vector into an initially empty list.
 */

#include <algorithm>  // std::sort, std::unique_copy
#include <iostream>   // std::cout
#include <iterator>   // std::back_inserter
#include <list>       // std::list
#include <vector>     // std::vector

/**
 * @brief Copies unique elements from vector to list
 * @param src The source vector
 * @param dest The destination list (must be empty)
 */
void CopyUniqueElements(const std::vector<int>& src, std::list<int>& dest) {
  // First sort the vector to group duplicates
  std::vector<int> sorted_vec = src;
  std::sort(sorted_vec.begin(), sorted_vec.end());

  // Copy unique elements to list
  std::unique_copy(sorted_vec.begin(), sorted_vec.end(),
                   std::back_inserter(dest));
}

int main() {
  std::vector<int> numbers = {9, 4, 5, 7, 4, 3, 5, 9, 1, 2, 3, 7, 8};
  std::list<int> unique_numbers;

  // Copy unique elements
  CopyUniqueElements(numbers, unique_numbers);

  // Print results
  std::cout << "Original vector: ";
  for (int n : numbers) std::cout << n << ' ';
  std::cout << "\nUnique elements: ";
  for (int n : unique_numbers) std::cout << n << ' ';
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-27.cc && ./main
 * Original vector: 9 4 5 7 4 3 5 9 1 2 3 7 8
 * Unique elements: 1 2 3 4 5 7 8 9
 */
