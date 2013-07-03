/*
 * Exercise 6.1: What is the difference between a parameter and an argument?
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates a function with parameters
 * @param formal_param1 This is a parameter (int)
 * @param formal_param2 This is another parameter (double)
 * @return float Result of computation
 *
 * Parameters are the variables declared in the function signature.
 * They represent the "slots" that will hold values passed to the function.
 */
float ExampleFunction(int formal_param1, double formal_param2) {
  /*
   * Within this function:
   * - formal_param1 and formal_param2 are parameters
   * - They behave like local variables
   * - Their values come from the arguments at call time
   */
  return formal_param1 * formal_param2;
}

/*
 * Technical Explanation:
 *
 * Key Differences:
 * 1. Parameters:
 *    - Variables declared in function declaration/definition
 *    - Part of function signature
 *    - Act as placeholders for incoming values
 *    - Have specified types and names
 *    - Scope limited to function body
 *
 * 2. Arguments:
 *    - Actual values passed to function during call
 *    - Can be literals, variables, or expressions
 *    - Must be compatible with parameter types
 *    - Evaluated before being passed
 *
 * Memory Considerations:
 * - Parameters are created when function is called
 * - Arguments are copied into parameters (by default)
 * - For class types, this copying can be expensive
 */

int main() {
  int actual_var = 5;           // Regular variable
  const double constant = 2.5;  // Named constant

  /*
   * Function call examples showing arguments:
   * - actual_var and kConstant are arguments
   * - 10 and 3.14 are also arguments (literals)
   */
  float result1 = ExampleFunction(actual_var, constant);  // Passing variables
  float result2 = ExampleFunction(10, 3.14);              // Passing literals
  float result3 =
      ExampleFunction(actual_var + 2, constant * 1.1);  // Expressions

  std::cout << "Results: " << result1 << ", " << result2 << ", " << result3
            << '\n';

  return 0;
}

/*
 * Common Pitfalls:
 * 1. Parameter-argument type mismatch
 * 2. Incorrect argument order
 * 3. Assuming arguments and parameters share memory (without references)
 * 4. Modifying parameters expecting it to affect arguments (without references)
 *
 * Best Practices:
 * 1. Use descriptive parameter names
 * 2. Keep parameter lists reasonably short
 * 3. Document parameter expectations
 * 4. Consider const correctness for parameters
 */

/* $ g++ -o main chapter-06/exercise-01.cc && ./main
 * Results: 12.5, 31.4, 19.25
 */
