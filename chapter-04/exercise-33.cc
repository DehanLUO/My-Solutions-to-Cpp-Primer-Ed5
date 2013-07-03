/*
 * Exercise 4.33: Using Table 4.12 (p. 166) explain what the following
 * expression does:
 *     someValue ? ++x, ++y : --x, --y;
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates comma operator and conditional operator precedence
 * @param condition Boolean determining which branch executes
 * @param x Reference to first integer (modified)
 * @param y Reference to second integer (modified)
 * @return The final value of y after expression evaluation
 */
int ExplainCommaOperator(bool condition, int& x, int& y) {
  // The expression parses as: (condition ? (++x, ++y) : --x), --y
  // Due to operator precedence (? : higher than comma)
  return condition ? ++x, ++y : --x, --y;
}

int main() {
  // Step 1: Initialize test values
  {
    int x = 10, y = 20;
    bool test_condition = true;

    // Step 2: Demonstrate with true condition
    std::cout << "Initial values: x=" << x << ", y=" << y << '\n';
    int result = ExplainCommaOperator(test_condition, x, y);
    std::cout << "After true condition: x=" << x << ", y=" << y
              << " (result=" << result << ")\n";
  }

  // Step 2: Demonstrate with false condition
  {
    int x = 10, y = 20;
    bool test_condition = false;
    int result = ExplainCommaOperator(test_condition, x, y);
    std::cout << "After false condition: x=" << x << ", y=" << y
              << " (result=" << result << ")\n";
  }
  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-33.cc && ./main
 * Initial values: x=10, y=20
 * After true condition: x=11, y=20 (result=20)
 * After false condition: x=9, y=19 (result=19)
 */
