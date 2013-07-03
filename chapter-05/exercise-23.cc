/*
 * Exercise 5.23: Write a program that reads two integers from the standard
 * input and prints the result of dividing the first number by the second.
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
  try {
    // Read input with validation
    int numerator = ReadInteger("Enter numerator (integer): ");
    int denominator = ReadInteger("Enter denominator (integer): ");

    // Perform and display division
    int result = SafeIntegerDivision(numerator, denominator);
    std::cout << "Result of " << numerator << " / " << denominator << " = "
              << result << '\n';

  } catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return -1;
  } catch (...) {
    std::cerr << "Unknown error occurred" << '\n';
    return -2;
  }

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-23.cc && ./main
 * Enter numerator (integer): 1
 * Enter denominator (integer): 0
 * Error: Division by zero is undefined
 */
