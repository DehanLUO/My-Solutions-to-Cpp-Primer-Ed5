/*
 * Exercise 1.14: Compare and contrast the loops that used a for with those
 * using a while. Are there advantages or disadvantages to using either form?
 */

#include <iostream>  // std::cin

int main() {
  // The `for` loop is designed for counted iterations with its self-contained
  // struction
  //     for (initialization; condition; update) { /* body */ }
  // - Bundles initialization, conditon checking, and increment/decrement in one
  //   line
  // - Ideal when the exact number of iterations is known beforehead (e.g..
  // array
  //   processing)
  // - Naturally limits loop variable scope to the loop
  // - Provides better readability for simple, liner progressions
  for (int num = 0; num < 10; ++num) {
    /* repeat 10 times */
  }

  //
  // The `while` loop handles conditional repetition with minimal syntax:
  //     while (condition) { /* body */ }
  // - Requires separate initialization and variable updates
  // - Preferred when termination depends on complex runtime conditions
  // - More flexible for non-liner control flow (multiple exit points/variable
  //   updates)
  // - Better for event-driven or sentinel-value patterns
  int input = 0;
  while (std::cin >> input && 0 != input) {
    /* process until 0 */
  }
}
