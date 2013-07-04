/*
 * Exercise 6.12: Rewrite the program from exercise 6.10 in § 6.2.1 (p. 210) to
 * use references instead of pointers to swap the value of two ints. Which
 * version do you think would be easier to use and why?
 */

#include <iostream>  // std::cout

/**
 * @brief Swaps the values of two integers using references
 * @param a Reference to first integer
 * @param b Reference to second integer
 *
 * Demonstrates:
 * 1. Pass-by-reference parameters
 * 2. Cleaner syntax than pointer version
 * 3. Direct modification of original variables
 */
void SwapIntegers(int& a, int& b) {
  int temp = a;  // Store value of a
  a = b;         // Assign value of b to a
  b = temp;      // Assign stored value to b
}

/*
 * Comparison with Pointer Version:
 *
 * Advantages of Reference Version:
 * 1. No need for null checks (references can't be null)
 * 2. Cleaner syntax (no dereferencing needed)
 * 3. More intuitive usage
 * 4. Compiler prevents invalid usage
 *
 * Advantages of Pointer Version:
 * 1. Can represent "no object" (nullptr)
 * 2. Can be reassigned to point to different objects
 * 3. Required for some low-level operations
 */

int main() {
  // Test case with references
  int x = 5, y = 10;
  std::cout << "Before swap: x = " << x << ", y = " << y << '\n';
  SwapIntegers(x, y);  // Just pass variables directly
  std::cout << "After swap: x = " << x << ", y = " << y << '\n';

  return 0;
}

/* $ g++ -o main chapter-06/exercise-12.cc && ./main
 * Before swap: x = 5, y = 10
 * After swap: x = 10, y = 5
 */