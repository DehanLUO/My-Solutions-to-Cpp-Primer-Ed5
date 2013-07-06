/*
 * Exercise 10.14: Write a lambda that takes two ints and returns their sum.
 */

#include <iostream>  // std::cout

int main() {
  // Lambda that takes two ints and returns their sum
  auto sum_lambda = [](int a, int b) -> int { return a + b; };

  // Test cases
  const int result1 = sum_lambda(3, 5);
  const int result2 = sum_lambda(-2, 7);
  const int result3 = sum_lambda(0, 0);

  std::cout << "3 + 5 = " << result1 << '\n'
            << "-2 + 7 = " << result2 << '\n'
            << "0 + 0 = " << result3 << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-14.cc && ./main
 * 3 + 5 = 8
 * -2 + 7 = 5
 * 0 + 0 = 0
 */
