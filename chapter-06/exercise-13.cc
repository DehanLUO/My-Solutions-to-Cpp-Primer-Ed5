/*
 * Exercise 6.13: Assuming T is the name of a type, explain the difference
 * between a function declared as void f(T) and void f(T&).
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates pass-by-value behavior
 * @param val A copy of the original value
 *
 * Changes made here won't affect the original
 */
void PassByValue(int val) {
  val = 100;  // Only modifies local copy
  std::cout << "Inside PassByValue: " << val << '\n';
}

/**
 * @brief Demonstrates pass-by-reference behavior
 * @param val Reference to the original value
 *
 * Changes made here affect the original
 */
void PassByReference(int& val) {
  val = 100;  // Modifies the original variable
  std::cout << "Inside PassByReference: " << val << '\n';
}

/*
 * Key Differences:
 *
 * 1. void f(T):
 *    - Receives a COPY of the argument
 *    - Original variable remains unchanged
 *    - More expensive for large objects
 *    - Use when you don't need to modify original
 *
 * 2. void f(T&):
 *    - Receives a REFERENCE to the original
 *    - Can modify the original variable
 *    - No copying occurs (more efficient)
 *    - Use when you need to modify original or avoid copy
 */

int main() {
  int x = 5;

  // Pass-by-value demonstration
  std::cout << "Before PassByValue: " << x << '\n';
  PassByValue(x);
  std::cout << "After PassByValue: " << x << "\n\n";
  // Value remains 5 (unchanged)

  // Pass-by-reference demonstration
  std::cout << "Before PassByReference: " << x << '\n';
  PassByReference(x);
  std::cout << "After PassByReference: " << x << '\n';
  // Value is now 100 (modified)

  return 0;
}

/* $ g++ -o main chapter-06/exercise-13.cc && ./main
 * Before PassByValue: 5
 * Inside PassByValue: 100
 * After PassByValue: 5
 *
 * Before PassByReference: 5
 * Inside PassByReference: 100
 * After PassByReference: 100
 */
