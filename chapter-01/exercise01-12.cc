/*
 * Exercise 1.12: What does the following for loop do? What is the final value
 * of sum?
 *     int sum = 0;
 *.    for (int i = -100; i <= 100; ++i)
 *.        sum += i;
 */
/*
 * This loop sums integers from -100 to 100. The final sum is 0 because positive
 * and negetive numbers cancel each other out.
 */

#include <iostream>  // std::cout

int main() {
  int sum = 0;
  for (int i = -100; i <= 100; ++i) sum += i;

  std::cout << sum << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise01-12.cc && ./main
 * 0
 */
