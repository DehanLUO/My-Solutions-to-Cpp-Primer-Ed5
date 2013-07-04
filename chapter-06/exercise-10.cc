

/*
 * Exercise 6.10: Using pointers, write a function to swap the values of two
 * ints. Test the function by calling it and printing the swapped values.
 */

#include <iostream>  // std::cout

/**
 * @brief Swaps the values of two integers using pointers
 * @param a Pointer to first integer
 * @param b Pointer to second integer
 *
 * Demonstrates:
 * 1. Pointer dereferencing
 * 2. Basic swap algorithm
 * 3. Pass-by-pointer parameter passing
 */
void SwapIntegers(int* a, int* b) {
  if (a == nullptr || b == nullptr) {
    // Handle null pointers
    return;
  }
  int temp = *a;  // Store value pointed by a
  *a = *b;        // Assign value pointed by b to a
  *b = temp;      // Assign stored value to b
}

/*
 * Implementation Notes:
 * 1. Uses dereference operator (*) to access values
 * 2. Temporary variable preserves value during swap
 * 3. Null check prevents undefined behavior
 * 4. Modifies original variables (not copies)
 */

int main() {
  // Test case 1: Normal values
  int x = 5, y = 10;
  std::cout << "Before swap: x = " << x << ", y = " << y << '\n';
  SwapIntegers(&x, &y);  // Pass addresses
  std::cout << "After swap: x = " << x << ", y = " << y << '\n';

  return 0;
}

/* $ g++ -o main chapter-06/exercise-10.cc && ./main
 * Before swap: x = 5, y = 10
 * After swap: x = 10, y = 5
 */
