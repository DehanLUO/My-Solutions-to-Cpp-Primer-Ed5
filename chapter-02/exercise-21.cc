/*
 * Exercise 2.21: Explain each of the following definitions. Indicate whether
 * any are illegal and, if so, why.
 *     int i = 0;
 *     (a) double* dp = &i;         (b) int *ip =i;        (c) int *p = &i;
 */

int main() {
  int i = 0;

  /*
   * Illegal. `dp` is a pointer to double, but `&i` is a pointer to int.
   */
  // double* dp = &i;

  /*
   * Illegal. `ip` is a pointer to int, but `i` is an int. A pointer must hold a
   * memory address, not an iteger value.
   */
  // int* ip = i;

  int* p = &i;  // Legal.

  return 0;
}
