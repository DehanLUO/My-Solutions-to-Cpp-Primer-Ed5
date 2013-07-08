/*
 * Exercise 13.31: Give your class a < operator and define a vector of HasPtrs.
 * Give that vector some elements and then sort the vector. Note when swap is
 * called.
 */

/*
 * - The swap function is used by std::sort during the sorting process
 * - The implementation shows how many swaps occur during a typical sort
 */

#include "exercise-31.h"  // HasPtr

#include <algorithm>  // std::sort
#include <iostream>   // std::cout
#include <vector>     // std::vector

int main() {
  std::cout << "=== Creating vector of HasPtr ===\n";
  std::vector<HasPtr> vec;
  vec.reserve(4);  // Preallocate to avoid reallocation during emplace

  vec.emplace_back("orange");
  vec.emplace_back("cherry");
  vec.emplace_back("banana");
  vec.emplace_back("apple");

  std::cout << "\n=== Before sorting ===\n";
  for (const auto& hp : vec) {
    std::cout << *hp << " ";
  }
  std::cout << "\n";

  std::cout << "\n=== Sorting vector ===\n";
  std::sort(vec.begin(), vec.end());

  std::cout << "\n=== After sorting ===\n";
  for (const auto& hp : vec) {
    std::cout << *hp << " ";
  }
  std::cout << "\n";

  std::cout << "\n=== End of scope ===\n";
  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-31.cc && ./main
 * === Creating vector of HasPtr ===
 *
 * === Before sorting ===
 * orange cherry banana apple
 *
 * === Sorting vector ===
 * ==> Executing swap between "orange" and "banana"
 * ==> Executing swap between "orange" and "apple"
 * ==> Executing swap between "cherry" and "apple"
 * ==> Executing swap between "banana" and "apple"
 *
 * === After sorting ===
 * apple banana cherry orange
 *
 * === End of scope ===
 */
