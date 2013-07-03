/*
 * Exercise 5.3: Use the comma operator (§ 4.10, p. 157) to rewrite the while
 * loop from § 1.4.1 (p. 11) so that it no longer requires a block. Explain
 * whether this rewrite improves or diminishes the readability of this code.
 */

#include <iostream>  // std::cout

/*
 * Diminishes readability because:
 * - Removes visual structure of the loop body
 * - Makes the two operations appear as one
 * - Violaes the one-statement-per-line guideline
 * Only advantage: Save vertical space (generally not worth it)
 */

int main() {
  int sum = 0, val = 1;
  // keep executing the while as long as val is less then or equal to 10
  while (val <= 10) sum += val, ++val;  // Comma operator version
  /*
   * {
   *   sum += val;  // assigns sum + val to sum
   *   ++val;       // add 1 to val
   * }
   */
  std::cout << "Sum of 1 to 10 inclusive is " << sum << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-03.cc && ./main
 * Sum of 1 to 10 inclusive is 55
 */
