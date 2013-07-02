/*
 * Exercise 4.17: Explain the difference between prefix and postfix increment.
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates prefix vs postfix increment behavior
 */
void ExplainIncrementOperators() {
  int x = 5, y = 5;
  int prefix_result, postfix_result;

  // Prefix increment: increments first, then returns new value
  prefix_result = ++x;

  std::cout << "Prefix increment (++x):\n";
  std::cout << "  New x value: " << x << "\n";
  std::cout << "  Returned value: " << prefix_result << "\n\n";

  // Postfix increment: returns original value, then increments
  postfix_result = y++;

  std::cout << "Postfix increment (y++):\n";
  std::cout << "  New y value: " << y << "\n";
  std::cout << "  Returned value: " << postfix_result << "\n";
}

int main() {
  ExplainIncrementOperators();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-17.cc && ./main
 * Prefix increment (++x):
 *   New x value: 6
 *   Returned value: 6
 *
 * Postfix increment (y++):
 *   New y value: 6
 *   Returned value: 5
 */