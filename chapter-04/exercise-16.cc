/*
 * Exercise 4.16: Although the following are legal, they probably do not behave
 * as the programmer expects. Why? Rewrite the expressions as you think they
 * should be.
 *     (a) if (p = getPtr() != 0)
 *     (b) if (i = 1024)
 */

#include <iostream>  // std::cout

/**
 * @brief Returns a test pointer for demonstration
 * @return int* Valid pointer if true, nullptr otherwise
 */
int* GetPtr(bool valid = true) {
  static int value = 42;
  return valid ? &value : nullptr;
}

int main() {
  // Case (a) Original: if (p = getPtr() != 0)
  {
    int* p;

    // Problem: Due to operator precedence, evaluates as p = (getPtr() != 0)
    // if (p = GetPtr() != 0) {  // Illegal. Assigns boolean result to pointer!
    // }

    // Corrected version (a):
    if ((p = GetPtr()) != 0) {  // Proper assignment then comparison
      std::cout << "\nCorrected (a):\n";
      std::cout << "p properly points to: " << *p << "\n";
    }
  }

  // Case (b) Original: if (i = 1024)
  {
    int i = 0;
    // Problem: Assignment always evaluates to 1024 (true)
    if (i = 1024) {  // Likely meant comparison
      std::cout << "\nOriginal (b) - WRONG:\n";
      std::cout << "i is: " << i << " (always true)\n";
    }

    // Corrected version (b):
    if (i == 1024) {  // Proper comparison
      std::cout << "\nCorrected (b):\n";
      std::cout << "This only executes if i was already 1024\n";
    }
  }

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-16.cc && ./main
 * chapter-04/exercise-16.cc:40:11: warning: using the result of an assignment as a condition without parentheses [-Wparentheses]
 *    40 |     if (i = 1024) {  // Likely meant comparison
 *       |         ~~^~~~~~
 * chapter-04/exercise-16.cc:40:11: note: place parentheses around the assignment to silence this warning
 *    40 |     if (i = 1024) {  // Likely meant comparison
 *       |           ^
 *       |         (       )
 * chapter-04/exercise-16.cc:40:11: note: use '==' to turn this assignment into an equality comparison
 *    40 |     if (i = 1024) {  // Likely meant comparison
 *       |           ^
 *       |           ==
 * 1 warning generated.
 *
 * Corrected (a):
 * p properly points to: 42
 *
 * Original (b) - WRONG:
 * i is: 1024 (always true)
 *
 * Corrected (b):
 * This only executes if i was already 1024
 */