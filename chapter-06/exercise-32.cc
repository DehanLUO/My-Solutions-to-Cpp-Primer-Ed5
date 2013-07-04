/*
 * Exercise 6.32: Indicate whether the following function is legal. If so,
 * explain what it does; if not, correct any errors and then explain it.
 *     int &get(int *arry, int index) { return arry[index]; }
 *     int main() {
 *       int ia[10];
 *       for (int i = 0; i != 10; ++i)
 *         get(ia, i) = i;
 *     }
 */

#include <iostream>  // std::cout

/**
 * @brief Returns a reference to an array element
 * @param arry Pointer to integer array
 * @param index Array index to access
 * @return int& Reference to the array element
 *
 * Legal because:
 * 1. Returns reference to existing array element
 * 2. Array elements outlive the function call
 * 3. Allows modification of array elements
 */
int& Get(int* arry, int index) { return arry[index]; }

int main() {
  int ia[10];

  // Sets each array element to its index
  for (int i = 0; i != 10; ++i) Get(ia, i) = i;

  // Prints array contents (0 1 2 3 4 5 6 7 8 9)
  for (int val : ia) std::cout << val << ' ';

  return 0;
}

/* $ g++ -o main chapter-06/exercise-32.cc && ./main
 * 0 1 2 3 4 5 6 7 8 9
 */
