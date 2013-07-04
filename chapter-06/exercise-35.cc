/*
 * Exercise 6.35: In the call to factorial, why did we pass val - 1 rather than
 * val--?
 */

#include <iostream>   // std::cout
#include <stdexcept>  // std::invalid_argument

/**
 * @brief Correct factorial implementation using val - 1
 * @param val Non-negative integer input
 * @return int Factorial of input value
 * @throws std::invalid_argument When negative input provided
 */
int Factorial(int val) {
  if (val < 0) {
    throw std::invalid_argument("Negative value in factorial computation");
  }
  if (val <= 1) {
    return 1;  // Base case
  }
  return val * Factorial(val - 1);  // Safe: val - 1 creates new value
}

/**
 * @brief Incorrect implementation demonstrating dangerous val-- usage
 * @warning Contains infinite recursion and undefined behavior
 */
int BadFactorial(int val) {
  if (val <= 1) {
    return 1;
  }
  /*
   * DANGEROUS IMPLEMENTATION:
   * 1. Infinite recursion - always passes original val first
   * 2. Undefined behavior - modifies and reads val in same expression
   */
  return val * BadFactorial(val--);  // WRONG: UB and infinite recursion
}

int main() {
  // Safe version
  std::cout << "Factorial(5): " << Factorial(5) << "\n";  // 120

  /*
   * Dangerous version - would crash due to:
   * 1. Infinite recursion (never reaches base case)
   * 2. Undefined behavior in return expression
   */
  // std::cout << "BadFactorial(5): " << BadFactorial(5) << "\n"; // CRASH

  return 0;
}
/* $ g++ -o main chapter-06/exercise-35.cc && ./main
 * chapter-06/exercise-35.cc:38:32: warning: unsequenced modification and access to 'val' [-Wunsequenced]
 *    38 |   return val * BadFactorial(val--);  // WRONG: UB and infinite recursion
 *       |          ~~~                   ^
 * 1 warning generated.
 * Factorial(5): 120
 */