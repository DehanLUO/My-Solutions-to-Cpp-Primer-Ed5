/*
 * Exercise 4.13: What are the values of i and d after each assignment?
 *     int i;      double d;
 *     (a) d = i = 3.5;           (b) i = d = 3.5
 */

#include <iostream>  // std::cout

int main() {
  // Case (a): d = i = 3.5;
  int i_a;
  double d_a;
  d_a = i_a = 3.5;  // Assignment right-to-left
  // Breakdown:
  // 1. i_a = 3.5 → int truncation (i_a = 3)
  // 2. d_a = i_a → double assignment (d_a = 3.0)

  // Case (b): i = d = 3.5;
  int i_b;
  double d_b;
  i_b = d_b = 3.5;  // Assignment right-to-left
  // Breakdown:
  // 1. d_b = 3.5 → double assignment (d_b = 3.5)
  // 2. i_b = d_b → int truncation (i_b = 3)

  std::cout << "Case (a) d = i = 3.5 results:\n"
            << "i: " << i_a << " (int)\n"
            << "d: " << d_a << " (double)\n\n"
            << "Case (b) i = d = 3.5 results:\n"
            << "d: " << d_b << " (double)\n"
            << "i: " << i_b << " (int)\n";

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-13.cc && ./main
 * chapter-04/exercise-13.cc:13:15: warning: implicit conversion from 'double' to 'int' changes value from 3.5 to 3 [-Wliteral-conversion]
 *    13 |   d_a = i_a = 3.5; // Assignment right-to-left
 *       |             ~ ^~~ 1 warning generated.
 * Case (a) d = i = 3.5 results:
 * i: 3 (int)
 * d: 3 (double)
 *
 * Case (b) i = d = 3.5 results:
 * d: 3.5 (double)
 * i: 3 (int)
 */