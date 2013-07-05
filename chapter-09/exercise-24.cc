/*
 * Exercise 9.24: Write a program that fetches the first element in a vector
 * using at, the subscript operator, front, and begin. Test your program on an
 * empty vector.
 */

#include <iostream>   // std::cout, std::cerr
#include <stdexcept>  // std::out_of_range
#include <vector>     // std::vector

/**
 * @brief Demonstrates different methods to access first vector element
 * @param vec The vector to test
 *
 * Shows four access methods with proper error handling:
 * 1. at()
 * 2. operator[]
 * 3. front()
 * 4. begin()
 */
void TestVectorAccess(std::vector<int>& vec) {
  std::cout << "Testing vector with " << vec.size() << " elements:\n";

  /* Method 1: at() - bounds-checked */
  try {
    int val_at = vec.at(0);
    std::cout << "1. at(0): " << val_at << "\n";
  } catch (const std::out_of_range& e) {
    std::cerr << "1. at(0) failed: " << e.what() << "\n";
  }

  /* Method 2: operator[] - unchecked */
  if (!vec.empty()) {
    int val_sub = vec[0];  // UB if empty, we guard with check
    std::cout << "2. operator[0]: " << val_sub << "\n";
  } else {
    std::cerr << "2. operator[0] failed: vector is empty\n";
  }

  /* Method 3: front() - requires non-empty */
  if (!vec.empty()) {
    int val_front = vec.front();
    std::cout << "3. front(): " << val_front << "\n";
  } else {
    std::cerr << "3. front() failed: vector is empty\n";
  }

  /* Method 4: begin() - must check against end() */
  if (vec.begin() != vec.end()) {
    int val_begin = *vec.begin();
    std::cout << "4. begin(): " << val_begin << "\n";
  } else {
    std::cerr << "4. begin() failed: vector is empty\n";
  }
}

int main() {
  // Test case 1: Non-empty vector
  std::vector<int> numbers = {10, 20, 30};
  TestVectorAccess(numbers);

  // Test case 2: Empty vector
  std::vector<int> empty_vec;
  TestVectorAccess(empty_vec);

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-24.cc && ./main
 * Testing vector with 3 elements:
 * 1. at(0): 10
 * 2. operator[0]: 10
 * 3. front(): 10
 * 4. begin(): 10
 * Testing vector with 0 elements:
 * 1. at(0) failed: vector
 * 2. operator[0] failed: vector is empty
 * 3. front() failed: vector is empty
 * 4. begin() failed: vector is empty
 */
