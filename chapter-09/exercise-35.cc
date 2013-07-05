/*
 * Exercise 9.35: Explain the difference between a vector’s capacity and its
 * size.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Demonstrates the difference between vector size and capacity
 *
 * Size: Number of actual elements in the vector
 * Capacity: Total storage space currently allocated
 */
void DemonstrateSizeVsCapacity() {
  std::vector<int> vec;

  // Initial state
  std::cout << "Initial state:\n";
  std::cout << "Size: " << vec.size() << "\n";
  std::cout << "Capacity: " << vec.capacity() << "\n\n";

  // Add some elements
  for (int i = 0; i < 10; ++i) {
    vec.push_back(i);
    std::cout << "After push_back(" << i << "):\n";
    std::cout << "Size: " << vec.size() << "\n";
    std::cout << "Capacity: " << vec.capacity() << "\n";
  }

  // Trim excess capacity
  vec.shrink_to_fit();
  std::cout << "\nAfter shrink_to_fit():\n";
  std::cout << "Size: " << vec.size() << "\n";
  std::cout << "Capacity: " << vec.capacity() << "\n";
}

int main() {
  DemonstrateSizeVsCapacity();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-35.cc && ./main
 * Initial state:
 * Size: 0
 * Capacity: 0
 *
 * After push_back(0):
 * Size: 1
 * Capacity: 1
 * After push_back(1):
 * Size: 2
 * Capacity: 2
 * After push_back(2):
 * Size: 3
 * Capacity: 4
 * After push_back(3):
 * Size: 4
 * Capacity: 4
 * After push_back(4):
 * Size: 5
 * Capacity: 8
 * After push_back(5):
 * Size: 6
 * Capacity: 8
 * After push_back(6):
 * Size: 7
 * Capacity: 8
 * After push_back(7):
 * Size: 8
 * Capacity: 8
 * After push_back(8):
 * Size: 9
 * Capacity: 16
 * After push_back(9):
 * Size: 10
 * Capacity: 16
 *
 * After shrink_to_fit():
 * Size: 10
 * Capacity: 10
 */
