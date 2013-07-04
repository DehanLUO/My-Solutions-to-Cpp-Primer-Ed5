/*
 * Exercise 6.21: Write a function that takes an int and a pointer to an int and
 * returns the larger of the int value or the value to which the pointer points.
 * What type should you use for the pointer?
 */

#include <iostream>  // std::cout

/**
 * @brief Returns the larger of an int or the int pointed to by a pointer
 * @param val Integer value
 * @param ptr Pointer to integer (should be non-null)
 * @return int The larger value
 *
 * The pointer should be to const int because:
 * 1. We only read through the pointer
 * 2. Doesn't need to modify the pointed-to value
 * 3. Can accept pointers to const or non-const ints
 */
int LargerValue(int val, const int* ptr) { return (val > *ptr) ? val : *ptr; }

/*
 * Key Points:
 * 1. Pointer type: const int*
 *    - Can point to const or non-const ints
 *    - Clearly indicates we won't modify through pointer
 *    - More flexible interface
 * 2. Safety:
 *    - Should verify ptr isn't null in real code
 * 3. Alternative:
 *    - Could use int* if modification was needed
 */

int main() {
  int x = 5;
  int y = 10;
  const int z = 15;

  // Test cases
  std::cout << LargerValue(20, &x) << '\n';  // 20 (val is larger)
  std::cout << LargerValue(3, &y) << '\n';   // 10 (pointer value is larger)
  std::cout << LargerValue(1, &z) << '\n';   // 15 (works with const)

  return 0;
}

/* $ g++ -o main chapter-06/exercise-21.cc && ./main
 * 20
 * 10
 * 15
 */
