/*
 * Exercise 6.7: Write a function that returns 0 when it is first called and
 * then generates numbers in sequence each time it is called again.
 */

#include <iostream>  // std::cout

/**
 * @brief Generates sequential numbers starting from 0
 * @return Current sequence number
 *
 * Behavior:
 * - Returns 0 on first call
 * - Returns 1, 2, 3,... on subsequent calls
 * Uses static local variable to maintain state between calls
 */
int SequenceGenerator() {
  static int counter = -1;  // Static local variable
  return ++counter;         // Increment before return
}

/*
 * Implementation Notes:
 * 1. Static variable initialized only once
 * 2. Persists between function calls
 */

int main() {
  // Demonstration
  std::cout << SequenceGenerator() << std::endl;  // 0
  std::cout << SequenceGenerator() << std::endl;  // 1
  std::cout << SequenceGenerator() << std::endl;  // 2
  std::cout << SequenceGenerator() << std::endl;  // 3

  return 0;
}

/* $ g++ -o main chapter-06/exercise-07.cc && ./main
 * 0
 * 1
 * 2
 * 3
 */
