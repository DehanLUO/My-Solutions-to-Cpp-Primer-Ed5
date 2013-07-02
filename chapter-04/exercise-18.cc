/*
 * Exercise 4.18: What would happen if the while loop on page 148 that prints
 * the elements from a vector used the prefix increment operator?
 *     auto pbeg = v.begin();
 *     while(pbeg != v.end() && *beg >= 0)
 *       cout << *pbeg++ << endl; // print the current value and advance pbeg
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates prefix vs postfix increment in vector iteration
 */
void ExplainVectorIncrement() {
  std::vector<int> v = {1, 2, 3, -1, 4};  // Test vector

  // Original version (postfix increment - CORRECT)
  std::cout << "Original (postfix increment):\n";
  auto pbeg = v.begin();
  while (pbeg != v.end() && *pbeg >= 0) {
    std::cout << *pbeg++ << "\n";  // Print then increment
  }

  // Modified version (prefix increment - BUGGY)
  std::cout << "\nModified (prefix increment):\n";
  pbeg = v.begin();
  while (pbeg != v.end() && *pbeg >= 0) {
    std::cout << *++pbeg << "\n";  // Increment then print
                                   // (SKIPS FIRST ELEMENT!)
  }
}

int main() {
  ExplainVectorIncrement();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-18.cc && ./main
 * Original (postfix increment):
 * 1
 * 2
 * 3
 *
 * Modified (prefix increment):
 * 2
 * 3
 * -1
 */