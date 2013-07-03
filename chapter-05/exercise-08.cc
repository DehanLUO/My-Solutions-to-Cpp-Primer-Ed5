/*
 * Exercise 5.8: What is a “dangling else”? How are else clauses resolved in
 * C++?
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates the dangling else problem and resolution
 */
void DemonstrateDanglingElse() {
  bool condition1 = true;
  bool condition2 = false;

  // Example 1: Ambiguous case (bad practice)
  if (condition1)
    if (condition2)
      std::cout << "Both conditions true\n";
  else  // Which if does this belong to?
      std::cout
          << "This appears to match outer if but actually matches inner if\n";

  // Example 2: Properly resolved in C++.
  if (condition1) {
    if (condition2) {
      std::cout << "Both conditions true\n";
    }
  } else {  // Add explicit braces to avoid dangling else
    std::cout << "Outer condition false\n";
  }
}

int main() {
  DemonstrateDanglingElse();

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-08.cc && ./main
 * chapter-05/exercise-08.cc:19:5: warning: add explicit braces to avoid dangling else [-Wdangling-else]
 *    19 |   else  // Which if does this belong to?
 *       |   ^
 * 1 warning generated.
 * This appears to match outer if but actually matches inner if
 */
