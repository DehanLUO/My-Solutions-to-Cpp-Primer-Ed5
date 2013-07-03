/*
 * Exercise 6.3: Write and test your own version of fact.
 */

#include <iostream>   // std::cout, std::cerr
#include <stdexcept>  // std::invalid_argument

/**
 * @brief Computes the factorial at compile time
 * @param val Non-negative integer
 * @return int Factorial result
 *
 * Used for constexpr/static_assert cases
 */
constexpr int FactorialConstexpr(int val) {
  return (val <= 1) ? 1 : val * FactorialConstexpr(val - 1);
}

/**
 * @brief Computes the factorial of a number with validation
 * @param val Positive integer to compute factorial for
 * @return int Factorial result
 * @throws std::invalid_argument for negative inputs
 *
 * Improvements over original:
 * 1. Input validation
 * 2. Better variable naming
 * 3. Exception safety
 */
int Factorial(int val) {
  if (val < 0) {
    throw std::invalid_argument("Factorial of negative numbers is undefined");
  }
  return FactorialConstexpr(val);
}

/**
 * @brief Tests the Factorial function with various cases
 *
 * Demonstrates proper testing methodology including:
 * 1. Basic cases
 * 2. Edge cases
 * 3. Exception cases
 */
void TestFactorial() {
  // Compile-time tests
  static_assert(FactorialConstexpr(0) == 1, "0! should equal 1");
  static_assert(FactorialConstexpr(1) == 1, "1! should equal 1");
  static_assert(FactorialConstexpr(5) == 120, "5! should equal 120");

  // Runtime output test
  std::cout << "Testing Factorial(7): " << Factorial(7) << " (Expected: 5040)"
            << std::endl;

  // Test exception handling
  try {
    auto result = Factorial(-3);
    std::cerr << "Error: Negative input test failed" << std::endl;
  } catch (const std::invalid_argument& e) {
    std::cout << "Successfully caught negative input: " << e.what()
              << std::endl;
  }
}

/*
 * Possible Extensions:
 * 1. Template version for different integer types
 * 2. Overflow detection
 * 3. Memoization for repeated calls
 * 4. constexpr version for compile-time computation
 */

int main() {
  TestFactorial();

  return 0;
}

/* $ g++ -o main chapter-06/exercise-05.cc && ./main
 * Testing Factorial(7): 5040 (Expected: 5040)
 * Successfully caught negative input: Factorial of negative numbers is undefined
 */
