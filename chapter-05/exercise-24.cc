/*
 * Exercise 5.24: Revise your program to throw an exception if the second number
 * is zero. Test your program with a zero input to see what happens on your
 * system if you don’t catch an exception.
 */

#include <iostream>   // std::cin, std::cout, std::cerr
#include <limits>     // std::numeric_limits<std::streamsize>
#include <stdexcept>  // std::runtime_error

/**
 * @brief Performs safe integer division with exception handling
 * @param numerator The dividend
 * @param denominator The divisor
 * @return int Result of the division
 * @throws std::runtime_error if denominator is zero
 *
 * Demonstrates proper exception handling for division operations
 * following C++ best practices.
 */
int SafeIntegerDivision(int numerator, int denominator) {
  if (denominator == 0) {
    throw std::runtime_error("Division by zero is undefined");
  }
  return numerator / denominator;
}

/**
 * @brief Reads an integer from standard input with validation
 * @param prompt Message to display before input
 * @return int Valid integer obtained from user
 *
 * Handles all possible input errors including:
 * - Non-integer input
 * - Out-of-range values
 * - Stream failures
 */
int ReadInteger(const std::string& prompt) {
  int value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      return value;
    }

    // Handle input failure
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Invalid input. Please enter an integer.\n";
  }
}

int main() {
  // Read input with validation
  int numerator = ReadInteger("Enter numerator (integer): ");
  int denominator = ReadInteger("Enter denominator (integer): ");

  // Perform and display division
  int result = SafeIntegerDivision(numerator, denominator);
  std::cout << "Result of " << numerator << " / " << denominator << " = "
            << result << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-24.cc && ./main
 * Enter numerator (integer): 1
 * Enter denominator (integer): 0
 * libc++abi: terminating due to uncaught exception of type std::runtime_error: Division by zero is undefined
 * [1]    78493 abort      ./main
 */
