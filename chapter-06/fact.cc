#include <stdexcept>

#include "Chapter6.h"

// Exercise 6.3 implementations

/**
 * @brief Computes the factorial at compile time
 */
constexpr int FactorialConstexpr(int val) {
  return (val <= 1) ? 1 : val * FactorialConstexpr(val - 1);
}

/**
 * @brief Computes the factorial with validation
 */
int Factorial(int val) {
  if (val < 0) {
    throw std::invalid_argument("Factorial of negative numbers is undefined");
  }
  return FactorialConstexpr(val);
}

/**
 * @brief Tests the Factorial function
 */
void TestFactorial() {
  // Compile-time tests
  static_assert(FactorialConstexpr(0) == 1, "0! should equal 1");
  static_assert(FactorialConstexpr(1) == 1, "1! should equal 1");
  static_assert(FactorialConstexpr(5) == 120, "5! should equal 120");

  // Runtime tests would go here
}

// Exercise 6.7 implementation

/**
 * @brief Generates sequential numbers
 */
int SequenceGenerator() {
  static int counter = -1;
  return ++counter;
}
