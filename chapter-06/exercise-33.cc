/*
 * Exercise 6.33: Write a recursive function to print the contents of a vector.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Recursively prints vector contents
 * @param vec The vector to print
 * @param index Current index (defaults to 0)
 *
 * Base case: When index reaches vector size
 * Recursive case: Print current element and process next index
 */
void PrintVectorRecursive(const std::vector<int>& vec, size_t index = 0) {
  // Base case: stop when we've processed all elements
  if (index >= vec.size()) {
    std::cout << '\n';  // Newline at end
    return;
  }

  // Print current element
  std::cout << vec[index] << ' ';

  // Recursive call for next element
  PrintVectorRecursive(vec, index + 1);
}

/*
 * Alternative version using iterators
 */
void PrintVectorRecursiveIt(std::vector<int>::const_iterator current,
                            std::vector<int>::const_iterator end) {
  if (current == end) {
    std::cout << '\n';
    return;
  }
  std::cout << *current << ' ';
  PrintVectorRecursiveIt(++current, end);
}

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5};

  std::cout << "Version 1 (index-based): ";
  PrintVectorRecursive(numbers);

  std::cout << "Version 2 (iterator-based): ";
  PrintVectorRecursiveIt(numbers.begin(), numbers.end());

  return 0;
}

/* $ g++ -o main chapter-06/exercise-33.cc && ./main
 * Version 1 (index-based): 1 2 3 4 5
 * Version 2 (iterator-based): 1 2 3 4 5
 */