/*
 * Exercise 2.14: Is the following program legal? If so, what values are
 * printed?
 *     int i = 100, sum = 0;
 *     for (int i = 0; i != 10; ++i)
 *       sum += i;
 *     std::cout << i << " " << sum << std::endl;
 */

#include <iostream>  // std::cout

int main() {
  /*
   * Outer `i` declared at the start of `main()`, with scope spanning the entire
   * function (except where shadowed). Unaffected by the inner `i` in the `for`
   * loop.
   */
  int i = 100, sum = 0;

  /*
   * Inner `i` is declared in the `for` loop, shadowing the outer `i`. This `i`
   * runs from 0 to 9, and its scope is limited to the loop. `sum += i`
   * accumulates the loop's `i` values:
   * sum = 0 + 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 = 45
   */
  for (int i = 0; i != 10; ++i) {
    sum += i;
  }

  /*
   * After the loop, the inner `i` goes out of scope, and the outer `i` (still
   * 100) is printed.
   */
  std::cout << i << " " << sum << std::endl;

  return 0;
}

/*
 * $ g++ -o main exercise-14.cc && ./main
 * 100 45
 */