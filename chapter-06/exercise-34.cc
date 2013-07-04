/*
 * Exercise 6.34: What would happen if the stopping condition in factorial were
 *     // calculate val!, which is 1 * 2 * 3 ... * val
 *     int factorial(int val){
 *       if (val > 1)
 *         return factorial(val - 1) * val;
 *       return 1;
 *     }
 */

#include <iostream>   // std::cout
#include <stdexcept>  // std::invalid_argument

/**
 * @brief Original factorial function with problematic stopping condition
 * @param val Input value
 * @return int Factorial of val
 *
 * Problem: Incorrect stopping condition leads to infinite recursion for
 * negative inputs
 */
int factorial(int val) {
  if (val != 0) return factorial(val - 1) * val;
  return 1;
}

/**
 * @brief Corrected factorial function
 * @param val Non-negative integer
 * @return int Factorial of val
 * @throws std::invalid_argument for negative inputs
 */
int Factorial(int val) {
  if (val < 0)
    throw std::invalid_argument("Factorial of negative numbers is undefined");
  if (val > 1)  // Proper stopping condition
    return Factorial(val - 1) * val;
  return 1;  // Base case: 0! = 1 and 1! = 1
}

/*
 * Key Problems with Original:
 * 1. Infinite recursion for negative numbers
 *    factorial(-1) → factorial(-2) → factorial(-3) → ...
 * 2. Stack overflow eventually occurs
 * 3. No input validation
 */

int main() {
  // Testing original (dangerous)
  std::cout << "Original (5): " << factorial(5) << '\n';  // 120
  // std::cout << "Original (-1): " << factorial(-1) << '\n';  // Crash!

  // Testing corrected version
  std::cout << "Corrected (5): " << Factorial(5) << '\n';  // 120
  try {
    std::cout << "Corrected (-1): " << Factorial(-1) << '\n';
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << '\n';  // Proper error handling
  }

  return 0;
}

/* $ g++ -o main chapter-06/exercise-34.cc && ./main
 * Original (5): 120
 * Corrected (5): 120
 * Corrected (-1): Error: Factorial of negative numbers is undefined
 */
