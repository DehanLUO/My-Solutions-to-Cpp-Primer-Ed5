/*
 * Exercise 4.14: Explain what happens in each of the if tests:
 *     if (42 = i) // ...
 *     if (i = 42) // ...
 */

#include <iostream>  // std::cout

int main() {
  int i = 0;

  // Case 1: if (42 = i)
  // This would cause a compilation error (commented out for demonstration)
  // if (42 = i) { /* ... */ }
  // Error: cannot assign to literal (lvalue required)

  // Case 2: if (i = 42)
  if (i = 42) {  // Assignment occurs, then evaluates i's new value
    std::cout << "Second if executed:\n";
    std::cout << "1. Assignment happens (i becomes 42)\n";
    std::cout << "2. Expression evaluates to 42 (non-zero → true)\n";
  }

  std::cout << "Final value of i: " << i << std::endl;
  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-14.cc && ./main
 * chapter-04/exercise-14.cc:18:9: warning: using the result of an assignment as a condition without parentheses [-Wparentheses]
 *    18 |   if (i = 42) {  // Assignment occurs, then evaluates i's new value
 *       |       ~~^~~~
 * chapter-04/exercise-14.cc:18:9: note: place parentheses around the assignment to silence this warning
 *    18 |   if (i = 42) {  // Assignment occurs, then evaluates i's new value
 *       |         ^
 *       |       (     )
 * chapter-04/exercise-14.cc:18:9: note: use '==' to turn this assignment into an equality comparison
 *    18 |   if (i = 42) {  // Assignment occurs, then evaluates i's new value
 *       |         ^
 *       |         ==
 * 1 warning generated.
 * Second if executed:
 * 1. Assignment happens (i becomes 42)
 * 2. Expression evaluates to 42 (non-zero → true)
 * Final value of i: 42
 */