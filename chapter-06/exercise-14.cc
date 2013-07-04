/*
 * Exercise 6.14: Give an example of when a parameter should be a reference
 * type. Give an example of when a parameter should not be a reference.
 */

#include <iostream>  // std::cout
#include <string>    // std::string

// Example 1: SHOULD be a reference
/**
 * @brief Modifies a string by appending text
 * @param str Reference to string to modify
 * @param text Text to append
 *
 * Uses reference because:
 * 1. We want to modify the original string
 * 2. Strings can be large (avoid copying)
 * 3. The change should be visible to caller
 */
void AppendToGreeting(std::string& str, const std::string& text) {
  str += text;
}

// Example 2: Should NOT be a reference
/**
 * @brief Calculates square of a number
 * @param num The number to square
 * @return Squared value
 *
 * Uses value parameter because:
 * 1. We don't need to modify original
 * 2. int is small (copy is cheap)
 * 3. No side effects needed
 */
int Square(int num) { return num * num; }

/*
 * When to use references:
 * 1. When you need to modify the original object
 * 2. When passing large objects (avoid copying)
 * 3. When the parameter is an "out" or "in-out" parameter
 *
 * When to use value parameters:
 * 1. When working with primitive types (int, double, etc.)
 * 2. When you want an independent copy
 * 3. When the parameter is input-only
 * 4. When the object is small and copying is cheap
 */

int main() {
  // Reference parameter example
  std::string greeting = "Hello";
  AppendToGreeting(greeting, ", World!");
  std::cout << greeting << '\n';  // Output: Hello, World!

  // Value parameter example
  int number = 5;
  int squared = Square(number);
  std::cout << number << " squared is " << squared << '\n';  // 5 squared is 25
  std::cout << "Original number unchanged: " << number << '\n';  // Still 5

  return 0;
}

/* $ g++ -o main chapter-06/exercise-14.cc && ./main
 * Hello, World!
 * 5 squared is 25
 * Original number unchanged: 5
 */
