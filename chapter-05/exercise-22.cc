/*
 * Exercise 5.22: The last example in this section that jumped back to begin
 * could be better written using a loop. Rewrite the code to eliminate the goto.
 *
 *   // backward jump over an initialized variable definition is okay
 * begin:
 *   int sz = get_size();
 *   if (sz <= 0) {
 *     goto begin;
 *   }
 */

#include <iostream>  // std::cin, std::cout

/**
 * @brief Simulates getting a size value (mock implementation)
 * @return An integer value representing size
 *
 * In a real implementation, this would get input from user
 * or other data source. Negative values trigger retry.
 */
int GetSize() {
  static int mock_values[] = {-1, -2, 0, 5};  // Test sequence
  static size_t index = 0;
  return mock_values[index++];
}

/**
 * @brief Demonstrates proper loop structure to replace backward goto
 *
 * Shows the idiomatic way to implement retry logic
 * without using goto statements.
 */
void BackwardJumpReplacement() {
  int sz;

  /*
   * Loop structure provides clear retry logic:
   * 1. Initialization happens before check
   * 2. Continue condition is explicit
   * 3. No variable scope issues
   */
  do {
    sz = GetSize();
  } while (sz <= 0);

  std::cout << "Valid size: " << sz << '\n';
}

int main() {
  BackwardJumpReplacement();

  return 0;
}
/*
 * $ g++ -o main chapter-05/exercise-22.cc && ./main
 * Valid size: 5
 */
