/*
 * Exercise 4.11: Write an expression that tests four values, a, b, c, and d,
 * and ensures that a is greater than b, which is greater than c, which is
 * greater than d.
 */

#include <iostream>  // std::cin, std::cout

/**
 * @brief Tests if four values are in strictly decreasing order
 * @return true if a > b > c > d, false otherwise
 */
bool IsStrictlyDecreasing(int a, int b, int c, int d) {
  return (a > b) && (b > c) && (c > d);
}

int main() {
  // Initialize four test values
  int a = 0, b = 0, c = 0, d = 0;

  // Get user input
  std::cout << "Enter four integers (space-separated): ";
  std::cin >> a >> b >> c >> d;

  // Test the condition
  if (IsStrictlyDecreasing(a, b, c, d)) {
    std::cout << "Condition met: " << a << " > " << b << " > " << c << " > "
              << d << "\n";
  } else {
    std::cout << "Condition failed\n";
  }

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-11.cc && ./main
 * Enter four integers (space-separated): 4 3 2 1
 * Condition met: 4 > 3 > 2 > 1
 */