/*
 * Exercise 10.15: Write a lambda that captures an int from its enclosing
 * function and takes an int parameter. The lambda should return the sum of the
 * captured int and the int parameter.
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates a lambda capturing a local variable
 * @param base_value The value to capture in the lambda
 */
void DemonstrateCapturingLambda(int base_value) {
  /*
   * Lambda capturing base_value by value and taking an int parameter
   * The capture list [base_value] copies the local variable
   */
  auto add_to_base = [base_value](int x) { return base_value + x; };

  std::cout << "Base value: " << base_value << '\n'
            << "Adding 5: " << add_to_base(5) << '\n'
            << "Adding -3: " << add_to_base(-3) << '\n'
            << "Adding 0: " << add_to_base(0) << '\n';
}

int main() {
  // Test with different captured values
  DemonstrateCapturingLambda(10);
  std::cout << '\n';
  DemonstrateCapturingLambda(-5);
  std::cout << '\n';
  DemonstrateCapturingLambda(0);

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-15.cc && ./main
 * Base value: 10
 * Adding 5: 15
 * Adding -3: 7
 * Adding 0: 10
 *
 * Base value: -5
 * Adding 5: 0
 * Adding -3: -8
 * Adding 0: -5
 *
 * Base value: 0
 * Adding 5: 5
 * Adding -3: -3
 * Adding 0: 0
 */
