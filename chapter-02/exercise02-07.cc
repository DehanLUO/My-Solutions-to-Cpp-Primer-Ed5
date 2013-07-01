/*
 * Exercise 2.7: What values do these literals represent? What type does each
 * have?
 *     (a) "Who goes with F\145rgus?\012"
 *     (b) 3.14e1L    (c) 1024f  (d) 3.14L
 */

#include "../include/type_util.h"

int main() {
  PRINT_VAR_TYPE("Who goes with F\145rgus?\012");  // char const*
  PRINT_VAR_TYPE(3.14e1L);                         // long double
  /*
   * `1024f` is incorrect in c++ because:
   * - `f` suffix must follow a floating-point number, but `1024` is an integer.
   * - To make `1024` a float, it must include a decimal point (e.g., 1024.f).
   */
  PRINT_VAR_TYPE(1024.f);  // float
  PRINT_VAR_TYPE(3.14L);   // long double

  return 0;
}

/*
 * $ g++ -o main exercise02-07.cc && ./main
 * "Who goes with F\145rgus?\012" = Who goes with Fergus?
 *  | type: char const*
 * 3.14e1L = 31.4 | type: long double
 * 1024.f = 1024 | type: float
 * 3.14L = 3.14 | type: long double
 */