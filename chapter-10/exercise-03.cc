/*
 * Exercise 10.3: Use accumulate to sum the elements in a vector<int>.
 */

#include <iostream>  // std::cout
#include <numeric>   // std::accumulate
#include <vector>    // std::vector

/*
 * Computes the sum of all elements in a vector of integers.
 * Demonstrates proper usage of std::accumulate with default addition.
 */
int SumVectorElements(const std::vector<int>& numbers) {
  /*
   * std::accumulate provides a generic way to reduce a sequence:
   * 1. Takes begin/end iterators
   * 2. Initial value (0 for summation)
   * 3. Binary operation (defaults to operator+)
   */
  return std::accumulate(numbers.begin(), numbers.end(), 0);
}

int main() {
  const std::vector<int> sample_data = {1, 2, 3, 4, 5};

  const int simple_sum = SumVectorElements(sample_data);

  std::cout << "Simple accumulate sum: " << simple_sum << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-03.cc && ./main
 * Simple accumulate sum: 15
 */
