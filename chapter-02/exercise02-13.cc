/*
 * Exercise 2.13: What is the value of j in the following program?
 *     int i = 42;
 *     int main() {
 *       int i = 100;
 *       int j = i;
 *     }
 */

#include <iostream>  // std::cout

int i = 42;

int main() {
  int i = 100;
  int j = i;

  /*
   * Inside `main()`, a new local variable `i` is declared and initialized to
   * 100. This shadows the global `i = 42` within the scope of `main()`.
   *
   * When `j` is initialized with `i`, the compiler uses the most local
   * definition of `i`. Since the local `i = 100` is in scope, `j` gets the
   * value of 100, not the global `i = 42`.
   */
  std::cout << i << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise02-13.cc && ./main
 * 100
 */