/*
 * Exercise 4.38: Explain the following expression:
 *     double slope = static_cast<double>(j/i);
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates integer division and type conversion pitfalls
 * @param j Numerator
 * @param i Denominator
 * @return Slope calculated with different conversion approaches
 */
double CalculateSlope(int j, int i) {
  // Original expression behavior:
  // 1. Performs integer division j/i (truncates fractional part)
  // 2. Converts the integer result to double
  double slope = static_cast<double>(j / i);

  return slope;
}

int main() {
  // Test case 1: 5/2
  int j = 5, i = 2;

  // Step 1: Show original expression behavior
  std::cout << "Original expression static_cast<double>(" << j << "/" << i
            << "): " << CalculateSlope(j, i) << '\n';

  // Step 2: Demonstrate proper floating-point division alternatives
  // Option A: Cast either operand before division
  double slopeA = static_cast<double>(j) / i;
  std::cout << "Proper conversion A: static_cast<double>(" << j << ")/" << i
            << ": " << slopeA << '\n';

  // Option B: Use floating-point literal
  double slopeB = j / (i * 1.0);
  std::cout << "Proper conversion B: " << j << "/(" << i << "*1.0): " << slopeB
            << '\n';

  // Step 3: Show integer division result for comparison
  std::cout << "Integer division result: " << j / i << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-38.cc && ./main
 * Original expression static_cast<double>(5/2): 2
 * Proper conversion A: static_cast<double>(5)/2: 2.5
 * Proper conversion B: 5/(2*1.0): 2.5
 * Integer division result: 2
 */
