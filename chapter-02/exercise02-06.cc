/*
 * Exercise 2.6: What, if any, are the differences between the following
 * definitions:
 *     int month = 9, day = 7;
 *     int month = 09, day = 07;
 */

int main() {
  int month = 9, day = 7;

  /*
   * int month = 09, day = 07;
   * Integer literals starting with `0` are interpreted as octal (base-8)
   * numbers. However, `09` is invalid in octal since the digit `9` does not
   * exist in octal (only 0-7 are allowed).
   */

  return 0;
}