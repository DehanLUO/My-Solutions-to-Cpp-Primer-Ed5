/*
 * Exercise 10.31: Update the program from the previous exercise so that it
 * prints only the unique elements. Your program should use unqiue_copy
 * (§ 10.4.1, p. 403).
 */

#include <algorithm>  // std::sort, std::unique_copy
#include <iostream>   // std::cin, std::cout
#include <iterator>   // std::istream_iterator, std::ostream_iterator
#include <vector>     // std::vector

int main() {
  // Read integers from standard input
  std::vector<int> numbers{std::istream_iterator<int>(std::cin),
                           std::istream_iterator<int>()};

  // Sort the numbers (required for unique_copy)
  std::sort(numbers.begin(), numbers.end());

  // Print only unique elements
  std::cout << "Unique sorted numbers: ";
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-31.cc && ./main
 * 34 21 13 8 5 3 2 1 1 0
 * Unique sorted numbers: 0 1 2 3 5 8 13 21 34
 */
