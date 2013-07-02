/*
 * Exercise 4.8: Explain when operands are evaluated in the logical AND, logical
 * OR, and equality operators.
 */

#include <iostream>  // std::cout

// Helper function to demonstrate evaluation
bool log(const char* name, bool result) {
  std::cout << "Evaluated: " << name << " = " << std::boolalpha << result
            << '\n';
  return result;
}

int main() {
  /*
   * Logicalk AND - Short-circuit evaluation:
   * - Left operand always evaluated first
   * - Right operand only evaluated if left is true
   */
  {
    std::cout << "Logical AND:\n";
    bool and_resut = log("A", false) && log("B", true);
    std::cout << "Result: " << and_resut << "\n\n";
  }

  /*
   * Logical OR - Short-circuit evaluation:
   * - Left operand always evaluated first
   * - Right operand only evaluated if left is false
   */
  {
    std::cout << "Logical OR:\n";
    bool or_result = log("C", true) || log("D", false);
    std::cout << "Result: " << or_result << "\n\n";
  }

  /*
   * Equality - No short-circuiting:
   * - Both operands always evaluated
   * - Evaluation order unspecified (compiler-dependent)
   */
  {
    std::cout << "Equality:\n";
    bool eq_result = log("E", true) == log("F", false);
    std::cout << "Result: " << eq_result << "\n";
  }

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-08.cc && ./main
 * Logical AND:
 * Evaluated: A = false
 * Result: false
 *
 * Logical OR:
 * Evaluated: C = true
 * Result: true
 *
 * Equality:
 * Evaluated: E = true
 * Evaluated: F = false
 * Result: false
 */