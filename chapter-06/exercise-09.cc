/*
 * Exercise 6.9: Write your own versions of the fact.cc and factMain.cc files.
 * These files should include your Chapter6.h from the exercises in the previous
 * section. Use these files to understand how your compiler supports separate
 * compilation.
 */

/*
 * exercise-09.cc
 * Main program using factorial functions from Chapter6.h
 */

#include <iostream>  // std::cout

#include "Chapter6.h"

int main() {
  // Exercise 6.3/6.4 demo
  std::cout << "Factorial demonstration:\n";
  try {
    std::cout << "5! = " << Factorial(5) << '\n';
    std::cout << "0! = " << Factorial(0) << '\n';
    std::cout << "-2! = " << Factorial(-2) << '\n';  // This will throw
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
  }

  // Exercise 6.5 demo
  std::cout << "\nAbsolute value demonstration:\n";
  std::cout << "AbsoluteValue(-5) = " << AbsoluteValue(-5) << '\n';
  std::cout << "AbsoluteValue(3.14) = " << AbsoluteValue(3.14) << '\n';

  // Exercise 6.7 demo
  std::cout << "\nSequence generator demonstration:\n";
  std::cout << "First call: " << SequenceGenerator() << '\n';
  std::cout << "Second call: " << SequenceGenerator() << '\n';
  std::cout << "Third call: " << SequenceGenerator() << '\n';

  return 0;
}

/* $ g++ -o main chapter-06/exercise-09.cc chapter-06/fact.cc && ./main
 * Factorial demonstration:
 * 5! = 120
 * 0! = 1
 * -2! = Error: Factorial of negative numbers is undefined
 *
 * Absolute value demonstration:
 * AbsoluteValue(-5) = 5
 * AbsoluteValue(3.14) = 3.14
 *
 * Sequence generator demonstration:
 * First call: 0
 * Second call: 1
 * Third call: 2
 */
