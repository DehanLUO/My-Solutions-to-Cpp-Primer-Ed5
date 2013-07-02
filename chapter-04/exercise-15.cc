/*
 * Exercise 4.15: The following assignment is illegal. Why? How would you
 * correct it?
 *     double dval; int ival; int *pi;
 *     dval = ival = pi = 0;
 */

#include <iostream>  // std::cout

int main() {
  double dval;
  int ival;
  int *pi;

  // Illegal original:
  // dval = ival = pi = 0;
  // Problem: Cannot assign 0 (int) directly to pointer pi

  // Corrected version 1 (explicit typing):
  dval = ival = 0;  // Works: chain of numeric assignments
  pi = nullptr;     // Proper pointer initialization

  // Corrected version 2 (single statement):
  dval = ival = 0, pi = nullptr;  // Comma operator separates expressions

  /*
   * Original issue:
   * 1. pi = 0 attempts implicit int-to-pointer conversion
   * 2. This is illegal in C++ (though some compilers allow as extension)
   *
   * Correct approaches:
   * a) Separate statements (version 1)
   * b) Use nullptr for pointers (version 2)
   * c) Use explicit cast: pi = reinterpret_cast<int*>(0)
   */

  return 0;
}
