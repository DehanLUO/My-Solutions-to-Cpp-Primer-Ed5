/*
 * Exercise 10.30: Use stream iterators, sort, and copy to read a sequence of
 * integers from the standard input, sort them, and then write them back to the
 * standard output.
 */

#include <algorithm>  // std::sort
#include <iostream>   // std::cin, std::cout
#include <iterator>   // std::istream_iterator, std::ostream_iterator
#include <vector>     // std::vector

int main() {
  // Create vector from input stream iterators
  std::istream_iterator<int> in_iter(std::cin), eof;
  std::vector<int> numbers(in_iter, eof);
  // std::vector<int> number{std::istream_iterator<int>(std::cin),
  //                         std::istream_iterator<int>()};

  // Sort the numbers
  std::sort(numbers.begin(), numbers.end());

  // Write sorted numbers to output
  std::cout << "Sorted numbers: ";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-30.cc && ./main
 * 34 21 13 8 5 3 2 1 1 0
 * Sorted numbers: 0 1 1 2 3 5 8 13 21 34
 */
