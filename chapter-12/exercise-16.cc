/*
 * Exercise 12.16: Compilers don’t always give easy-to-understand error messages
 * if we attempt to copy or assign a unique_ptr. Write a program that contains
 * these errors to see how your compiler diagnoses them.
 */

#include <memory>  // std::unique_ptr

int main() {
  // initialization
  std::unique_ptr<int> p1(new int(42));
  std::unique_ptr<int> p2(new int(100));

  // Error 1: Copy construction (commented for compilation)
  /*
   * chapter-12/exercise-16.cc:20:24: error: call to implicitly-deleted copy constructor of 'std::unique_ptr<int>'
   *    20 |   std::unique_ptr<int> p3(p1);  // Will not compile
   *       |                        ^  ~~
   */
  // std::unique_ptr<int> p3(p1);  // Will not compile

  // Error 2: Copy assignment (commented for compilation)
  /*
   * chapter-12/exercise-16.cc:23:6: error: object of type 'std::unique_ptr<int>' cannot be assigned because its copy assignment operator is implicitly deleted
   *    28 |   p2 = p1;  // Will not compile
   *       |      ^
   */
  // p2 = p1;  // Will not compile

  // Correct approach 1: Move semantics
  std::unique_ptr<int> p4(std::move(p1));  // p1 now nullptr
  p2 = std::move(p4);                      // p4 now nullptr

  // Correct approach 2: Release/reset
  int* raw_p = p2.release();
  std::unique_ptr<int> p5(raw_p);

  return 0;
}
