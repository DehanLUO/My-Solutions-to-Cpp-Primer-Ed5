/*
 * Exercise 2.12: Which, if any, of the following names are invalid?
 *     (a) int double = 3.14;                    (b) int _;
 *     (c) int catch-22;                         (d) int 1_or_2 = 1;
 *     (e) double Double = 3.14;
 */

int main() {
  /*
   * Invalid. `double` is a c++ keyword (reserved for the `double` type).
   */
  // int double = 3.14;

  int _;  // Valid.

  /*
   * Invalid. Hyphens (-) are not allowed in identifiers. The compiler
   * interprets `catch-22` as subtraction.
   */
  // int catch-22;

  /*
   * Invalid. Identifiers cannot start with a digit.
   */
  // int 1_or_2 = 1;

  double Double = 3.14;  // Valid.

  return 0;
}
