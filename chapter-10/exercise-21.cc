/*
 * Exercise 10.21: Write a lambda that captures a local int variable and
 * decrements that variable until it reaches 0. Once the variable is 0
 * additional calls should no longer decrement the variable. The lambda should
 * return a bool that indicates whether the captured variable is 0.
 */

#include <iostream>  // std::cout

int main() {
  int counter = 5;  // Initial value

  // Lambda that captures counter by reference and decrements it
  auto decrement_to_zero = [&counter]() -> bool {
    if (counter > 0) {
      --counter;
    }
    return counter == 0;
  };

  // Test the lambda
  while (!decrement_to_zero()) {
    std::cout << "Counter decremented to " << counter << '\n';
  }

  std::cout << "Final counter value: " << counter << '\n';

  // Additional calls after reaching 0
  std::cout << "After reaching 0:\n";
  for (int i = 0; i < 3; ++i) {
    bool is_zero = decrement_to_zero();
    std::cout << "Call " << i + 1 << ": " << counter
              << " (is_zero: " << std::boolalpha << is_zero << ")\n";
  }

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-21.cc && ./main
 * Counter decremented to 4
 * Counter decremented to 3
 * Counter decremented to 2
 * Counter decremented to 1
 * Final counter value: 0
 * After reaching 0:
 * Call 1: 0 (is_zero: true)
 * Call 2: 0 (is_zero: true)
 * Call 3: 0 (is_zero: true)
 */
