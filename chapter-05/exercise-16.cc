/*
 * Exercise 5.16: The while loop is particularly good at executing while some
 * condition holds; for example, when we need to read values until end-of-file.
 * The for loop is generally thought of as a step loop: An index steps through a
 * range of values in a collection. Write an idiomatic use of each loop and then
 * rewrite each using the other loop construct. If you could use only one loop,
 * which would you choose? Why?
 */

#include <iostream>  // std::cin, std::cout
#include <vector>    // std::vector

/**
 * @brief Demonstrates idiomatic while loop usage for input processing
 * @return Number of values successfully read
 */
int WhileLoopInput() {
  int count = 0;
  int input_value;
  /*
   * While loop is preferred for conditional iteration when:
   * 1. Termination depends on complex conditions
   * 2. Number of iterations is unknown beforehand
   * 3. Processing requires mid-loop condition checks
   */
  while (std::cin >> input_value) {
    ++count;
    // Additional processing would occur here
  }
  return count;
}

/**
 * @brief Demonstrates idiomatic for loop usage for collection traversal
 * @param container The collection to process
 * @return Sum of all elements
 */
int ForLoopCollection(const std::vector<int>& container) {
  int sum = 0;
  /*
   * For loop is preferred for sequenced iteration when:
   * 1. Iterating through known quantity of elements
   * 2. Index/iterator management is required
   * 3. Step patterns are regular and predictable
   */
  for (auto it = container.begin(); it != container.end(); ++it) {
    sum += *it;
  }
  return sum;
}

/**
 * @brief Converts while loop logic to for loop implementation
 * @return Number of values successfully read
 */
int WhileToForConversion() {
  int count = 0;
  for (int input_value; std::cin >> input_value; ++count) {
    // Processing occurs within the loop body
  }
  return count;
}

/**
 * @brief Converts for loop logic to while loop implementation
 * @param container The collection to process
 * @return Sum of all elements
 */
int ForToWhileConversion(const std::vector<int>& container) {
  int sum = 0;
  auto it = container.begin();
  while (it != container.end()) {
    sum += *it;
    ++it;
  }
  return sum;
}

/*
 * Comparative analysis of loop constructs:
 *
 * The while loop's strength lies in its simplicity for conditional iteration,
 * particularly when dealing with unpredictable input patterns or complex
 * termination conditions. Its minimal syntax focuses attention on the
 * continuation condition.
 *
 * The for loop provides superior structure for sequenced iteration by
 * combining initialization, condition checking, and increment operations
 * in a single visible line. This explicit grouping prevents common errors
 * of omission in loop control.
 *
 * If constrained to a single loop construct, the for loop would be more
 * versatile as it can simulate while loop behavior through creative use of
 * its three components, while maintaining better control structure visibility.
 * The while loop cannot as easily replicate the for loop's index management
 * without external variables.
 */

int main() {
  // Note: Actual execution would require proper initialization
  const std::vector<int> sample_data = {1, 2, 3, 4, 5};

  // Idiomatic implementations
  // WhileLoopInput(); // Requires cin input
  ForLoopCollection(sample_data);

  // Converted implementations
  // WhileToForConversion(); // Requires cin input
  ForToWhileConversion(sample_data);

  return 0;
}
