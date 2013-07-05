/*
 * Exercise 9.36: Can a container have a capacity less than its size?
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Demonstrates that a container's capacity cannot be less than its size
 */
void ProveCapacityAlwaysGreaterOrEqual() {
  std::vector<int> vec = {1, 2, 3, 4, 5};  // size = 5, capacity ≥ 5

  std::cout << "Initial state:\n";
  std::cout << "Size: " << vec.size() << "\n";
  std::cout << "Capacity: " << vec.capacity() << "\n\n";

  // Attempt to force capacity < size (impossible)
  vec.resize(10);       // Increase size
  vec.shrink_to_fit();  // Attempt to minimize capacity

  std::cout << "After resize and shrink_to_fit:\n";
  std::cout << "Size: " << vec.size() << "\n";
  std::cout << "Capacity: " << vec.capacity() << "\n\n";

  // Mathematical proof
  if (vec.capacity() < vec.size()) {
    std::cout << "ERROR: Capacity is less than size!\n";
  } else {
    std::cout << "As expected: capacity >= size (" << vec.capacity()
              << " >= " << vec.size() << ")\n";
  }
}

int main() {
  ProveCapacityAlwaysGreaterOrEqual();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-36.cc && ./main
 * Initial state:
 * Size: 5
 * Capacity: 5
 *
 * After resize and shrink_to_fit:
 * Size: 10
 * Capacity: 10
 *
 * As expected: capacity >= size (10 >= 10)
 */
