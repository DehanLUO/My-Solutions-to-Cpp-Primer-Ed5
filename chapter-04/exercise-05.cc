/*
 * Exercise 4.5: Determine the result of the following expressions.
 * (a) -30 * 3 + 21 / 5
 * (b) -30 + 3 * 21 / 5
 * (c) 30 / 3 * 21 % 5
 * (d) -30 / 3 * 21 % 4
 */

#include <iostream>  // std::cout

int main() {
  // Equivalent to: (-30 * 3) + (21 / 5)
  // -90 + 4(integer division truncates) = -86
  std::cout << -30 * 3 + 21 / 5 << '\n';

  // Equivalent to: -30 + ((3 * 21) / 5)
  // -30 + (63 / 5) = -30 + 12(integer division truncates) = -18
  std::cout << -30 + 3 * 21 / 5 << '\n';

  // Equivalent to: ((30 / 3) * 21) % 5
  // (10 * 21) % 5 = 210 % 5 = 0
  std::cout << 30 / 3 * 21 % 5 << '\n';

  // Equivalent to: ((-30 / 3) * 21) % 4
  // (-10 * 21) % 4 = -210 % 4 = -2 (sign follows dividend)
  std::cout << -30 / 3 * 21 % 4 << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-05.cc && ./main
 * -86
 * -18
 * 0
 * -2
 */