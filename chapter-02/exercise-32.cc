/*
 * Exercise 2.32: Is the following code legal or not? If not, how might you make
 * it legal?
 *     int null = 0, *p = null;
 */

int main() {
  /*
   * `null` is an int.
   * `p` is a pointer to int. At declaration time, `p` should initialized with
   * a value of type `int*`. However, `null` yields an `int` (even thouth its
   * value is 0), and `int` cannot be implicitly converted to `int*` only the
   * literal '0' or `nullptr` can.
   */
  // int null = 0, *p = null;

  return 0;
}