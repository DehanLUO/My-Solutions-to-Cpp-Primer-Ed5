/*
 * Exercise 3.29: List some of the drawbacks of using an array instead of a
 * vector.
 */

#include <vector>  // std::vector

void func(int arr[]) {}  // Actually int* arr
void func(const std::vector<int>& vec) {}

int main() {
  /*
   * Fixed Size
   * Arrays have a static size (must be known at compile time).
   * Vectpr can be dynamically resize.
   */
  int arr[10];            // Fixed size (10 elements)
  std::vector<int> ivec;  // Can grow with vec.push_back();

  /*
   * No Bounds Checking
   * Arrays do not check out-of-bounds access.
   * vectors support `at()`
   */
  arr[10] = 42;      // Undefined behaviour
  ivec.at(10) = 42;  // Throws std::out_of_range

  /*
   * Harder to Pass to Functions
   * Arrays decay to pointers, losing size info
   * vectors keep their size when passed.
   */
  func(arr);   // Passes a pointer (decays from int[10] to int*). Size info lost
  func(ivec);  // Size preserved

  /*
   * No Built-in Helpers
   * Arrays lack `.size()`, `.push_back()`, etc.
   * vectors provide many useful methods.
   */
  int arr_size = sizeof(arr) / sizeof(arr[0]);  // Manual size check
  int ivec_size = ivec.size();                  // Simple & safe

  /*
   * Less Safe Initeialization
   * Arrays may leave elements uninitialized.
   * vectors initialize elements automatically.
   */
  int arr_init[10];                   // Garbage values
  std::vector<int> ivec_init(10, 0);  // All 10 elements = 0

  return 0;
}
