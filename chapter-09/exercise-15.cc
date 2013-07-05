/*
 * Exercise 9.15: Write a program to determine whether two vector<int>s are
 * equal.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Determines if two vectors are equal
 *
 * Demonstrates three approaches:
 * 1. Direct operator== comparison
 * 2. Manual element-by-element comparison
 */
void CompareVectors() {
  std::vector<int> vec1{1, 2, 3, 4, 5};
  std::vector<int> vec2{1, 2, 3, 4, 5};
  std::vector<int> vec3{1, 2, 3};

  // Method 1: Direct comparison (recommended)
  bool method1 = (vec1 == vec2);       // true
  bool method1_diff = (vec1 == vec3);  // false

  // Method 2: Manual comparison
  bool method2 = true;
  if (vec1.size() != vec2.size()) {
    method2 = false;
  } else {
    for (size_t i = 0; i < vec1.size(); ++i) {
      if (vec1[i] != vec2[i]) {
        method2 = false;
        break;
      }
    }
  }

  // Print results
  std::cout << std::boolalpha;
  std::cout << "Method 1 (equal): " << method1 << '\n';
  std::cout << "Method 1 (different): " << method1_diff << '\n';
  std::cout << "Method 2 (equal): " << method2 << '\n';
}

int main() {
  CompareVectors();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-15.cc && ./main
 * Method 1 (equal): true
 * Method 1 (different): false
 * Method 2 (equal): true
 */