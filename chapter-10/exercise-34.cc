/*
 * Exercise 10.34: Use reverse_iterators to print a vector in reverse order.
 */

#include <iostream>  // std::cout
#include <iterator>  // std::reverse_iterator
#include <vector>    // std::vector

int main() {
  std::vector<int> vec = {1, 2, 3, 4, 5};

  // Print vector in reverse using reverse_iterator
  std::cout << "Vector in reverse order: ";
  for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit) {
    std::cout << *rit << " ";
  }
  std::cout << "\n";

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-34.cc && ./main
 * Vector in reverse order: 5 4 3 2 1
 */
