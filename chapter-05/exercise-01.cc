/*
 * Exercise 5.1: What is a null statement? When might you use a null statement?
 */

#include <iostream>  // std::cin, std::cout

int main() {
  // Example 1: Basic null statement (just a semicolon)
  ;  // This is a null statement

  // Example 2: Common use case - loop with all work in condition
  int count = 0;
  while (std::cin >> count && 0 != count)  // Condition does all the work
    ;                                      // Null statement as loop body
  std::cout << "Read " << count << " as input\n";

  // Example 3: Null statement in for loop
  int sum = 0;
  for (int i = 0; i < 10; sum += i, ++i)  // All work in increment
    ;                                     // Null statement
  std::cout << "Sum of 0-9: " << sum << '\n';

  // Example 4: Dangerous case - accidental null statement
  if (sum > 5)
    ;  // Note the accidental semicolon!
  {
    std::cout << "This will always execute due to the null statement\n";
  }

  return 0;
}
/* $ g++ -o main chapter-05/exercise-01.cc && ./main
 * 1 2 3 0
 * Read 0 as input
 * Sum of 0-9: 45
 * This will always execute due to the null statement
 */
