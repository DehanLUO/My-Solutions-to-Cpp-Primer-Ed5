/*
 * Exercise 2.15: Which of the following definitions, if any, are invalid? Why?
 *     (a) int ival = 1.01;            (b) int &rval1 = 1.01;
 *     (c) int &rval2 = ival;          (d) int &rval3
 */

int main() {
  int ival = 1.01;  // Valid. 1.01 is narrowed to 1.

  /*
   * Invalid. You cannot bind an `int&` to a literal integer.
   */
  // int &rval1 = 1.01;

  // Valid. It is correctly bound to the existing `int` object `ival`.
  int &rval2 = ival;

  /*
   * A reference must be initialized when declared.
   */
  // int &rval3;

  return 0;
}
