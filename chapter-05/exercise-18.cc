/*
 * Exercise 5.18: Explain each of the following loops. Correct any problems you
 * detect.
 *     (a) do
 *           int v1, v2;
 *           cout << "Please enter two numbers to sum:" ;
 *           if (cin >> v1 >> v2)
 *             cout << "Sum is: " << v1 + v2 << endl;
 *         while (cin);
 *     (b) do {
 *           // ...
 *         } while (int ival = get_response());
 *     (c) do {
 *           int ival = get_response();
 *         } while (ival);
 */

#include <iostream>  // std::cin, std::cout

/**
 * @brief Demonstrates proper do-while loop structure
 *
 * Analyzes and corrects three common do-while loop anti-patterns,
 * highlighting proper variable scoping and loop control.
 */

/*
 * Problem (a) Analysis:
 *
 * Corrected version demonstrates:
 * 1. Clear loop structure
 */
void CorrectedLoopA() {
  int v1 = 0;
  int v2 = 0;

  do {
    std::cout << "Please enter two numbers to sum: ";
    if (std::cin >> v1 >> v2) std::cout << "Sum is: " << v1 + v2 << '\n';
  } while (std::cin);
}

/*
 * Problem (b) Analysis:
 *
 * Original issues:
 * 1. Variable declaration in while condition is illegal
 *
 * Corrected version demonstrates:
 * 1. Proper variable declaration scope
 * 2. Explicit loop control
 */
int GetResponse() {
  // Mock implementation
  static int count = 3;
  return count--;
}

void CorrectedLoopB() {
  int ival;
  do {
    // Process response
    ival = GetResponse();
  } while (ival != 0);  // Explicit termination condition
}

/*
 * Problem (c) Analysis:
 *
 * Original issues:
 * 1. ival declared inside loop not visible in condition
 *
 * Corrected version demonstrates:
 * 1. Proper variable scope management
 */
void CorrectedLoopC() {
  int ival;
  do {
    ival = GetResponse();
    // Process response here
  } while (ival != 0);
}

/*
 * Comprehensive Do-While Loop Guidelines:
 *
 * 1. Variable Scope:
 *    - Variables needed in condition must be declared outside loop
 *    - Avoid declarations that span iterations unless necessary
 *
 * 2. Termination Conditions:
 *    - Should be explicit and verifiable
 *    - Avoid implicit conversions or unclear logic
 *
 * 3. Input Handling:
 *    - Always validate input streams
 *    - Provide clear exit mechanisms
 *
 * 4. Structural Considerations:
 *    - Prefer while loops when possible
 *    - Reserve do-while for guaranteed first iteration cases
 *    - Ensure at least one iteration is always desired
 */

int main() {
  // Demonstrate corrected implementations
  CorrectedLoopA();
  CorrectedLoopB();
  CorrectedLoopC();

  return 0;
}
