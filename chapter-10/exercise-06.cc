/*
 * Exercise 10.6: Using fill_n, write a program to set a sequence of int values
 * to 0.
 */

#include <algorithm>  // std::fill_n
#include <iostream>   // std::cout
#include <vector>     // std::vector

int main() {
  std::vector<int> numbers(
      10);  // a sequence of 10 ints (default-initialized to 0)

  // Fill the entire vector with 0s explicitly using fill_n
  std::fill_n(numbers.begin(), numbers.size(), 1);

  // Print the result to verify
  for (int num : numbers) {
    std::cout << num << ' ';
  }
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-06.cc && ./main
 * 1 1 1 1 1 1 1 1 1 1
 */
