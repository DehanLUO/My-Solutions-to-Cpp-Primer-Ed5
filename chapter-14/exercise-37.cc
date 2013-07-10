/*
 * Exercise 14.37: Write a class that tests whether two values are equal. Use
 * that object and the library algorithms to write a program to replace all
 * instances of a given value in a sequence.
 */

#include <algorithm>  // std::replace_if
#include <iostream>   // std::cout
#include <vector>     // std::vector

/**
 * @class EqualityTester
 * @brief Functor class that tests whether two values are equal
 *
 * This class provides a function object that compares two values for equality.
 * It can be used with standard library algorithms that require binary
 * predicates.
 */
class EqualityTester {
 public:
  /**
   * @brief Constructs an EqualityTester with a reference value for comparison
   * @param value The value to compare against
   */
  explicit EqualityTester(const int value) : reference_value_(value) {}

  /**
   * @brief Function call operator that performs equality comparison
   * @param others The value to compare with the reference value
   * @return bool True if values are equal, false otherwise
   * @time Complexity O(1)
   * @space Complexity O(1)
   */
  bool operator()(const int others) const { return reference_value_ == others; }

 private:
  int reference_value_;  // the value to compare against
};

int main() {
  std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5};

  EqualityTester tester(2);
  std::replace_if(numbers.begin(), numbers.end(), tester, 99);

  for (auto num : numbers) {
    std::cout << num << ' ';
  }
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-37.cc && ./main
 * 1 99 3 99 4 99 5
 */
