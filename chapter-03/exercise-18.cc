/*
 * Exercise 3.18: Is the following program legal? If not, how might you fix it?
 *     vector<int> ivec;
 *     ivec[0] = 42
 */

#include <vector>  // std::vector

int main() {
  std::vector<int> ivec;  // vector to store the integers

  //`ivec` is an empty vector; there are no elements to subscript
  // ivec[0] = 42;

  // The right way to write is to use push_back or emplace_back
  ivec.push_back(42);
  ivec.emplace_back(42);

  /*
   * Preallocate with constructor. Creates vector with 1 element (value 42)
   * // This uses the vector<T>(n, val) constructor, equivalent to :
   * std::vector<int> jvec(1);  // size = 1, (value = 0)
   * jvec[0] = 42;
   */
  std::vector<int> jvec(1, 42);

  // Initializer list. Creates vector with single element 42
  std::vector<int> kvec{42};

  return 0;
}
