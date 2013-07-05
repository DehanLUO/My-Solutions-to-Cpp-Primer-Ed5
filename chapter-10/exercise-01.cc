/*
 * Exercise 10.1: The algorithm header defines a function named count that, like
 * find, takes a pair of iterators and a value. count returns a count of how
 * often that value appears. Read a sequence of ints into a vector and print the
 * count of how many elements have a given value.
 */

#include <algorithm>  // std::count
#include <cstdlib>    // EXIT_SUCCESS
#include <iostream>   // std::cin, std::cout
#include <vector>     // std::vector

/*
 * Counts occurrences of a target value in a vector of integers.
 * Demonstrates proper usage of STL algorithms with iterator interfaces.
 */
size_t CountValueOccurrences(const std::vector<int>& numbers,
                             int target_value) {
  // The const qualifier ensures we don't modify the input vector
  return std::count(numbers.begin(), numbers.end(), target_value);
}

/*
 * Reads space-separated integers from standard input into a vector.
 * Shows robust input handling with clear termination conditions.
 */
std::vector<int> ReadIntVectorFromInput() {
  std::vector<int> result;
  int current_value;

  /*
   * Using while-loop with cin extraction operator demonstrates:
   * 1. Automatic type checking through stream operations
   * 2. Natural termination on non-integer input
   */
  while (std::cin >> current_value) {
    result.push_back(current_value);
  }

  // Clear failbit to allow subsequent input operations
  std::cin.clear();
  return result;
}

int main() {
  std::cout << "Enter target value to count:\n";
  int target_value;
  std::cin >> target_value;

  std::cout << "Enter integers separated by spaces (non-integer to stop):\n";
  const std::vector<int> numbers = ReadIntVectorFromInput();

  const size_t count = CountValueOccurrences(numbers, target_value);
  std::cout << "The value " << target_value << " appears " << count
            << " times\n";

  return EXIT_SUCCESS;
}

/*
 * $ g++ -o main chapter-10/exercise-01.cc && ./main
 * Enter target value to count:
 * 1
 * Enter integers separated by spaces (non-integer to stop):
 * 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * The value 1 appears 3 times
 */
