/*
 * What type should be used as the index into a vector of ints?
 */

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Demonstration of proper vector indexing
 *
 * The correct type is:
 * - std::vector<int>::size_type (container-specific)
 * - Or std::size_t (generic unsigned type)
 *
 * Rationale:
 * 1. Matches vector's size() return type
 * 2. Guaranteed to hold any valid index
 * 3. Consistent with standard library interfaces
 */
void DemonstrateIndexing() {
  std::vector<int> numbers{1, 2, 3, 4, 5};

  // Preferred container-specific type
  std::vector<int>::size_type idx1 = 0;
  for (; idx1 < numbers.size(); ++idx1) {
    std::cout << numbers[idx1] << ' ';  // Access elements with operator[]
  }
  std::cout << '\n';

  // Alternative portable type
  std::size_t idx2 = 0;
  for (; idx2 < numbers.size(); ++idx2) {
    std::cout << numbers[idx2] << ' ';  // Also correct
  }
  std::cout << '\n';
}

int main() {
  DemonstrateIndexing();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-07.cc && ./main
 * 1 2 3 4 5
 * 1 2 3 4 5
 */
