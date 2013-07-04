/*
 * Exercise 6.11: Write and test your own version of reset that takes a
 * reference.
 */

#include <iostream>  // std::cout

/**
 * @brief Resets a variable to 0 using reference
 * @param i Reference to integer to reset
 *
 * Demonstrates:
 * 1. Pass-by-reference parameter
 * 2. Direct modification of original variable
 * 3. Simpler syntax compared to pointer version
 */
void reset(int &i) {
  i = 0;  // Directly modifies the original variable
}

/*
 * Implementation Notes:
 * 1. No dereferencing needed (unlike pointer version)
 * 2. Cannot be called with literals (reset(42) is invalid)
 * 3. More intuitive syntax than pointer version
 */

/**
 * @brief Tests the reset function
 */
void test_reset() {
  int x = 42;
  std::cout << "Before reset: x = " << x << '\n';
  reset(x);
  std::cout << "After reset: x = " << x << '\n';
}

int main() {
  test_reset();

  return 0;
}

/* $ g++ -o main chapter-06/exercise-11.cc && ./main
 * Before reset: x = 42
 * After reset: x = 0
 */