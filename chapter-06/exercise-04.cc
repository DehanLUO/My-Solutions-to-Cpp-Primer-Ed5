/*
 * Exercise 6.4: Write a function that interacts with the user, asking for a
 * number and generating the factorial of that number. Call this function from
 * main.
 */

#include <iostream>   // std::cout, std::cerr
#include <stdexcept>  // std::invalid_argument

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

  int result = 1;
  for (int current = val; current > 1; --current) {
    result *= current;
  }
  return result;
}

int main() {
  // Interactive demonstration
  std::cout << "Enter a number to compute factorial: ";
  int input;
  if (std::cin >> input) {
    try {
      std::cout << input << "! = " << Factorial(input) << '\n';
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << '\n';
    }
  }

  return 0;
}

/* $ g++ -o main chapter-06/exercise-04.cc && ./main
 * Enter a number to compute factorial: 5
 * 5! = 120
 * $ ./main
 * Enter a number to compute factorial: -1
 * -1! = Error: Factorial of negative numbers is undefined
 */
