/*
 * Exercise 4.36: Assuming i is an int and d is a double write the expression i
 * *= d so that it does integral, rather than floating-point, multiplication.
 */

#include <iostream>  // std::cout

/**
 * @brief Performs integral multiplication with mixed int/double operands
 * @param i The integer value (will be modified)
 * @param d The double value to multiply by
 */
void IntegralMultiply(int& i, double d) {
  // Explicit cast to perform integral multiplication
  i *= static_cast<int>(d);

  // Alternative solution using compound assignment:
  // i = i * static_cast<int>(d);
}

int main() {
  // Step 1: Initialize variables
  int i = 9;
  double d = 3.142;

  std::cout << "Before: i = " << i << ", d = " << d << '\n';

  // Step 2: Perform integral multiplication
  IntegralMultiply(i, d);

  // Step 3: Show results
  std::cout << "After integral multiplication: i = " << i << '\n';

  // Step 4: Compare with floating-point multiplication
  int j = 9;
  j *= d;  // Implicit floating-point multiplication
  std::cout << "With floating-point multiplication: " << j << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-36.cc && ./main
 * Before: i = 9, d = 3.142
 * After integral multiplication: i = 27
 * With floating-point multiplication: 28
 */
