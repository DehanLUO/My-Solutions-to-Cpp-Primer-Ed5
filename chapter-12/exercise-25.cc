/*
 * Exercise 12.25: Given the following new expression, how would you delete pa?
 *     int *pa = new int[10];
 */

int main() {
  int* pa = new int[10];  // Array allocation

  /*
   * Defensive programming practices:
   * 1. Immediately assign nullptr after deletion
   * 2. Verify allocation success in production code
   * 3. Consider using smart pointers in modern C++
   */
  delete[] pa;
  pa = nullptr;  // Prevent dangling pointer

  return 0;
}
