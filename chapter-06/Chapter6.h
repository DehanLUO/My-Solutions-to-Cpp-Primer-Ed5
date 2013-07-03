#ifndef CHAPTER_06_CHAPTER6_H_
#define CHAPTER_06_CHAPTER6_H_

// Exercise 6.3: Factorial functions
/**
 * @brief Computes the factorial at compile time
 * @param val Non-negative integer
 * @return int Factorial result
 *
 * Used for constexpr/static_assert cases
 */
constexpr int FactorialConstexpr(int val);
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
int Factorial(int val);
/**
 * @brief Tests the Factorial function with various cases
 *
 * Demonstrates proper testing methodology including:
 * 1. Basic cases
 * 2. Edge cases
 * 3. Exception cases
 */
void TestFactorial();

// Exercise 6.5: Absolute value function
/**
 * @brief Returns the absolute value of a number
 * @tparam T Numeric type (int, double, etc.)
 * @param val Input value
 * @return Absolute value of the input
 *
 * Features:
 * - Works with all standard numeric types
 * - Compile-time type checking
 * - Simple and efficient implementation
 */
template <typename T>
T AbsoluteValue(T val) {
  return val < 0 ? -val : val;
}

// Exercise 6.7: Sequence generator
/**
 * @brief Generates sequential numbers starting from 0
 * @return Current sequence number
 *
 * Behavior:
 * - Returns 0 on first call
 * - Returns 1, 2, 3,... on subsequent calls
 * Uses static local variable to maintain state between calls
 */
int SequenceGenerator();

#endif  // CHAPTER_06_CHAPTER6_H_