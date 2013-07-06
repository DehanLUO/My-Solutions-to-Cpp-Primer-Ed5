/*
 * Exercise 10.35: Now print the elements in reverse order using ordinary
 * iterators.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

int main() {
  std::vector<int> vec = {1, 2, 3, 4, 5};

  // Print vector in reverse using ordinary iterators
  std::cout << "Vector in reverse order: ";
  for (auto it = vec.end(); it != vec.begin();) {
    std::cout << *(--it) << " ";  // Decrement before dereference
  }
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-35.cc && ./main
 * Vector in reverse order: 5 4 3 2 1
 */
