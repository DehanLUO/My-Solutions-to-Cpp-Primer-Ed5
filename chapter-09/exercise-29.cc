/*
 * Exercise 9.29: Given that vec holds 25 elements, what does vec.resize(100)
 * do? What if we next wrote vec.resize(10)?
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Demonstrates vector resize behavior
 *
 * Shows effects of:
 * 1. resize() to larger size
 * 2. resize() to smaller size
 * 3. Default value initialization
 */
void DemonstrateResize() {
  std::vector<int> vec(25);  // Vector with 25 elements (value-initialized to 0)

  std::cout << "Initial state:\n";
  std::cout << "Size: " << vec.size() << '\n';
  std::cout << "Capacity: " << vec.capacity() << "\n\n";

  /* Case 1: Resize to larger size (100) */
  vec.resize(100);

  std::cout << "After vec.resize(100):\n";
  std::cout << "Size: " << vec.size() << "\n";
  std::cout << "Capacity: " << vec.capacity() << "\n";
  std::cout << "Last element: " << vec[99] << " (value-initialized)\n\n";

  /* Case 2: Resize to smaller size (10) */
  vec.resize(10);

  std::cout << "After vec.resize(10):\n";
  std::cout << "Size: " << vec.size() << "\n";
  std::cout << "Capacity: " << vec.capacity() << "\n";
  std::cout << "Note: Capacity remains at " << vec.capacity()
            << " (no reallocation)\n";
  // Elements 10-99 are destroyed (but memory may remain allocated)

  vec.shrink_to_fit();
  std::cout << "Update capacity at " << vec.capacity() << '\n';
}

int main() {
  DemonstrateResize();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-29.cc && ./main
 * Initial state:
 * Size: 25
 * Capacity: 25
 *
 * After vec.resize(100):
 * Size: 100
 * Capacity: 100
 * Last element: 0 (value-initialized)
 *
 * After vec.resize(10):
 * Size: 10
 * Capacity: 100
 * Note: Capacity remains at 100 (no reallocation)
 * Update capacity at 10
 */
