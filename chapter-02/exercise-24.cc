/*
 * Exercise 2.24: Why is the initialization of p legal but that of lp illegal?
 *     int i = 42;         void *p = &i;               long *lp = &i;
 */

int main() {
  int i = 42;

  /*
   * A `void*` is a type-erased pointer designed to store addresses of any type.
   * It sacrifices type safety for flexibility.
   */
  void *p = &i;

  /*
   * `&i` is an int*, but `lp` expects a long*. c++ forbids implicit conversions
   * betwwen pointers to unrelated types (even if int and long are the same
   * size).
   */
  // long *p = &i;
  return 0;
}
