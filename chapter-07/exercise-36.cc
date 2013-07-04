/*
 * Exercise 7.36: The following initializer is in error. Identify and fix the
 * problem.
 *     struct X {
 *       X (int i, int j): base(i), rem(base % j) { }
 *       int rem, base;
 *     };
 */

#include <iostream>  // std::cout

/*
 * Exercise 7.36 Solution
 * Problem: The struct initialization order issue
 * Analysis:
 *   - Members are initialized in declaration order (rem before base)
 *   - Current code uses uninitialized 'base' to calculate 'rem'
 * Solution:
 *   - Reorder member declarations to match initialization needs
 */
struct X {
  int base, rem;  // Corrected declaration order
  X(int i, int j) : base(i), rem(base % j) {}
};

/**
 * @brief Demonstrates corrected struct initialization
 * @param i First constructor parameter
 * @param j Second constructor parameter
 */
void DemonstrateInitialization(int i, int j) {
  /*
   * Key considerations:
   *  - Class members initialize in declaration order
   *  - Using members before initialization is undefined behavior
   */
  X example(i, j);

  // Verification output
  std::cout << "Constructed with base=" << example.base
            << ", rem=" << example.rem << '\n';
}

int main() {
  DemonstrateInitialization(10, 3);  // Expected: base=10, rem=1
  return 0;
}

/* $ g++ -o main chapter-07/exercise-36.cc && ./main
 * Constructed with base=10, rem=1
 */
