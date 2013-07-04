/*
 * Exercise 6.22: Write a function to swap two int pointers.
 */

#include <iostream>  // std::cout

/**
 * @brief Swaps two int pointers
 * @param a Pointer to first int pointer
 * @param b Pointer to second int pointer
 *
 * Swaps what the pointers point to, not the pointers themselves
 */
void SwapIntPointers(int** a, int** b) {
  int* temp = *a;
  *a = *b;
  *b = temp;
}

/*
 * Alternative version that swaps the pointers themselves
 * (requires pointers to be passed by reference)
 */
void SwapPointersByReference(int*& a, int*& b) {
  int* temp = a;
  a = b;
  b = temp;
}

int main() {
  int x = 5, y = 10;
  int* px = &x;
  int* py = &y;

  std::cout << "Before swap:\n";
  std::cout << "*px = " << *px << " (x = " << x << ")\n";
  std::cout << "*py = " << *py << " (y = " << y << ")\n";

  // Using pointer-to-pointer version
  SwapIntPointers(&px, &py);

  std::cout << "\nAfter SwapIntPointers:\n";
  std::cout << "*px = " << *px << " (now points to y)\n";
  std::cout << "*py = " << *py << " (now points to x)\n";
  std::cout << "Original values unchanged: x = " << x << ", y = " << y << "\n";

  // Using reference version
  SwapPointersByReference(px, py);

  std::cout << "\nAfter SwapPointersByReference:\n";
  std::cout << "*px = " << *px << " (back to x)\n";
  std::cout << "*py = " << *py << " (back to y)\n";

  return 0;
}

/* $ g++ -o main chapter-06/exercise-22.cc && ./main
 * Before swap:
 * *px = 5 (x = 5)
 * *py = 10 (y = 10)
 *
 * After SwapIntPointers:
 * *px = 10 (now points to y)
 * *py = 5 (now points to x)
 * Original values unchanged: x = 5, y = 10
 *
 * After SwapPointersByReference:
 * *px = 5 (back to x)
 * *py = 10 (back to y)
 */