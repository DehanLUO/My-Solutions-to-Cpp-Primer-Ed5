/*
 * Exercise 6.52: Given the following declarations,
 *     void manip(int, int);
 *     double dobj;
 * what is the rank (§ 6.6.1, p. 245) of each conversion in the following
 * calls?
 *     (a) manip('a', 'z');
 *     (b) manip(55.4, dobj);
 */

#include <iostream>  // std::cout

// Supporting implementation
void manip(int a, int b) {
  std::cout << "manip(int, int) called with: " << a << ", " << b << '\n';
}

int main() {
  // Case (a): manip('a', 'z')
  /*
   * Conversion sequence:
   * - Both arguments are char
   * - Conversion from char to int:
   *   * Rank: Promotion (char → int is integral promotion)
   */
  manip('a', 'z');

  // Case (b): manip(55.4, dobj)
  /*
   * Conversion sequence:
   * - First argument is double literal 55.4
   * - Second argument is double variable dobj
   * - Conversion from double to int:
   *   * Rank: Arithmetic conversion (floating-integral conversion)
   */
  double dobj = 3.14;
  manip(55.4, dobj);

  return 0;
}

/* $ g++ -o main chapter-06/exercise-52.cc && ./main
 * chapter-06/exercise-52.cc:37:9: warning: implicit conversion from 'double' to 'int' changes value from 55.4 to 55 [-Wliteral-conversion]
 *    37 |   manip(55.4, dobj);
 *       |   ~~~~~ ^~~~
 * 1 warning generated.
 * manip(int, int) called with: 97, 122
 * manip(int, int) called with: 55, 3
 */
