/*
 * Exercise 2.20: What does the following program do?
 *     int i = 42;
 *     int *p1 = &i;
 *     *p1 = *p1 * *p1;
 */

int main() {
  int i = 42;    // Declares an integer i and initializes it to 42.
  int* p1 = &i;  // Declares a point p1 and sets it to point to i.

  /*
   * Deference(*p1) p1 to access i, then squares it value(*p1 * *p1), and
   * assigns the result back to i via *p1.
   */
  *p1 = *p1 * *p1;
}
