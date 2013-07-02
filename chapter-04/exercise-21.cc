/*
 * Exercise 4.21: Write a program to use a conditional operator to find the
 * elements in a vector<int> that have odd value and double the value of each
 * such element.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Doubles odd values in a vector using conditional operator
 * @param vec The vector to process (modified in-place)
 */
void DoubleOdds(std::vector<int>& vec) {
  for (auto& num : vec) {
    // Conditional operator checks for odd, doubles if true
    num = (0 != num % 2) ? num * 2 : num;
  }
}

int main() {
  // Initialize test vector
  std::vector<int> numbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Print original values
  std::cout << "Original vector:\n";
  for (const int& num : numbers) {
    std::cout << num << ' ';
  }
  std::cout << '\n';

  // Process vector
  DoubleOdds(numbers);

  // Print modified values
  std::cout << "\nAfter doubling odds:\n";
  for (const int& num : numbers) {
    std::cout << num << ' ';
  }
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-21.cc && ./main
 * Original vector:
 * 0 1 2 3 4 5 6 7 8 9
 *
 * After doubling odds:
 * 0 2 2 6 4 10 6 14 8 18
 */