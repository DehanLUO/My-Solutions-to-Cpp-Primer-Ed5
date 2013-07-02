/*
 * Exercise 2.3: What output will the following code produce?
 *     unsigned u = 10, u2 = 42;
 *     std::cout << u2 - u << std::endl;
 *     std::cout << u - u2 << std::endl;
 *     int i = 10, i2 = 42;
 *     std::cout << i2 - i << std::endl;
 *     std::cout << i - i2 << std::endl;
 *     std::cout << i - u << std::endl;
 *     std::cout << u - i << std::endl;
 */

#include <iostream>  // std::cout

int main() {
  unsigned u = 10, u2 = 42;
  // (unsigned)42 - (unsigned)10 = (unsigned)32
  std::cout << u2 - u << std::endl;
  /*
   * (unsigned)10 - (unsigned)42 = (unsigned)-32
   * Negative values cannot be represented in unsigned types
   * The result wraps modulo 2^{32} (for 32-bit `unsigned`)
   * = -32 mod 2^{32} = 2^32 - 32 = 4294967264
   */
  std::cout << u - u2 << std::endl;

  int i = 10, i2 = 42;
  // (int)42 - (int)10 = (int)32
  std::cout << i2 - i << std::endl;
  // (int)10 - (int)42 = (int)-32
  std::cout << i - i2 << std::endl;

  /*
   * (int)10 - (unsigned)10
   *
   * Step 1: Type promotion hierarchy.
   * [basic.fundamental] The `unsigned` keyword by itself implies `unsigned
   * int`.
   * Both `(int)10` and `(unsigned)10` are already at or above `int` rank,
   * so no further promotion occurs.
   *
   * Step 2: Signed vs. Unsigned Mismatch
   * [conv.integral] When signed and unsigned types of same rank collide in an
   * operation, the signed operand converts to unsigned.
   * = (unsigned)10 - (unsigned)10 = (unsigned)0
   */
  std::cout << i - u << std::endl;
  /*
   * (unsigned)10 - (int)10
   * = (unsigned)10 - (unsigned)10
   * = (unsigned)0
   */
  std::cout << u - i << std::endl;

  return 0;
}