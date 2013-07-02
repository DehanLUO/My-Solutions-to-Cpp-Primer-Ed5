/*
 * Exercise 4.9: Explain the behavior of the condition in the following if:
 *     const char *cp = "Hello World";
 *     if (cp && *cp)
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates pointer truthiness evaluation in conditions
 */
void ExplainPointerCondition() {
  const char *cp = "Hello World";  // cp points to string literal

  // The condition checks:
  // 1. cp   - Is pointer non-null? (true, points to valid address)
  // 2. *cp  - Does dereferenced pointer yield non-zero char? (true, 'H' != 0)
  if (cp && *cp) {
    /*
     * `cp` evaluates to true because it is a non-null pointer (holds address of
     * string literal)
     * `*cp` evaluates to true because it idereferences to 'H' (ASCII 72 != 0)
     * The condition is equivalent to `if (true && true)`
     */
    std::cout << "Condition passed: "
              << "Pointer is valid and points to non-null character\n";
  }
}

int main() {
  // Execute the demonstration
  ExplainPointerCondition();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-09.cc && ./main
 * Condition passed: Pointer is valid and points to non-null character
 */