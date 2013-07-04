/*
 * Exercise 6.50: Given the declarations for f from page 242, list the viable
 * functions, if any for each of the following calls. Indicate which function is
 * the best match, or if the call is illegal whether there is no match or why
 * the call is ambiguous.
 *     (a) f(2.56, 42)
 *     (b) f(42)
 *     (c) f(42, 0)
 *     (d) f(2.56, 3.14)
 */

#include <iostream>  // std::cout

// The declaration for f from page 242
// Supporting implementations
void f() { std::cout << "f()\n"; }
void f(int a) { std::cout << "f(int)\n"; }
void f(int a, int b) { std::cout << "f(int,int)\n"; }
void f(double a, double b = 3.14) { std::cout << "f(double,double)\n"; }

int main() {
  /*
   * Viable functions:
   * 1. f(int, int) - requires double->int and int exact
   * 2. f(double, double=3.14) - requires int->double
   *
   * Conversion costs by parameter:
   * - First argument:
   *     - f(int, int): narrowing (double to int)
   *     - f(double, double): exact match
   *     → f(double, double) wins
   *
   * - Second argument:
   *     - f(int, int): exact match
   *     - f(double, double): promotion (int to double)
   *     → f(int, int) wins
   *
   * Result:
   * - Each candidate wins on one parameter
   * - No candidate is better in all argument positions
   * - Therefore, the call is ambiguous
   */
  std::cout << "(a) f(2.56, 42): ambiguous\n";
  // f(2.56, 42);  // Calls f(double,double)

  /*
   * Viable functions:
   * 1. f(int) - exact match
   * 2. f(double=3.14) from f(double,double) - requires int->double
   *
   * Best match: f(int) - exact match beats promotion
   */
  std::cout << "(b) f(42): ";
  f(42);  // Calls f(int)

  /*
   * Viable functions:
   * 1. f(int, int) - exact match for both
   * 2. f(double, double=3.14) - requires int->double for both
   *
   * Best match: f(int, int) - exact match beats promotion
   */
  std::cout << "(c) f(42, 0): ";
  f(42, 0);  // Calls f(int,int)

  /*
   * Viable functions:
   * 1. f(int, int) - requires double->int for both (narrowing)
   * 2. f(double, double=3.14) - exact match for first, default not used
   *
   * Best match: f(double, double) - exact match beats narrowing
   */
  std::cout << "(d) f(2.56, 3.14): ";
  f(2.56, 3.14);  // Calls f(double,double)

  return 0;
}

/* $ g++ -o main chapter-06/exercise-50.cc && ./main
 * (a) f(2.56, 42): ambiguous
 * (b) f(42): f(int)
 * (c) f(42, 0): f(int,int)
 * (d) f(2.56, 3.14): f(double,double)
 */
