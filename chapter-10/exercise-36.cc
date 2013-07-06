/*
 * Exercise 10.36: Use find to find the last element in a list of ints with
 * value 0.
 */

#include <algorithm>  // std::find
#include <iostream>   // std::cout
#include <list>       // std::list

int main() {
  std::list<int> lst = {1, 2, 0, 4, 5, 0, 7, 8};

  // Find last 0 using reverse iterators
  auto rit = std::find(lst.rbegin(), lst.rend(), 0);

  if (rit != lst.rend()) {
    // Convert reverse iterator to regular iterator
    auto it = rit.base();  // Points one past the found element
    std::cout << "Last zero found at position: "
              << std::distance(lst.begin(), --it) << "\n";
    std::cout << "Value after last zero: " << *rit.base() << "\n";
  } else {
    std::cout << "No zero found in the list\n";
  }

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-36.cc && ./main
 * Last zero found at position: 5
 * Value after last zero: 7
 */
