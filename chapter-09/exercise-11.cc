/*
 * Exercise 9.11: Show an example of each of the six ways to create and
 * initialize a vector. Explain what values each vector contains.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Print vector contents
 */
void PrintVector(const std::vector<int>& vec) {
  for (auto num : vec) {
    std::cout << num << ' ';
  }
  std::cout << '\n';
}

/**
 * @brief Demonstration of vector initialization methods
 */
void DemonstrateVectorInitialization() {
  // 1. Default initialization - empty vector
  std::vector<int> v1;  // v1 contains: {}
  PrintVector(v1);

  // 2. Count and value initialization
  std::vector<int> v2(5, 10);  // v2 contains: {10, 10, 10, 10, 10}
  PrintVector(v2);

  // 3. Range initialization (from array)
  int arr[] = {1, 2, 3, 4, 5};
  std::vector<int> v3(arr, arr + 3);  // v3 contains: {1, 2, 3}
  PrintVector(v3);

  // 4. Copy initialization (from another vector)
  std::vector<int> v4(v2);  // v4 contains: {10, 10, 10, 10, 10}
  PrintVector(v4);

  // 5. Initializer list (C++11)
  std::vector<int> v5{1, 3, 5, 7, 9};  // v5 contains: {1, 3, 5, 7, 9}
  PrintVector(v5);

  // 6. Move initialization (C++11)
  std::vector<int> v6(
      std::move(v5));  // v6 contains: {1, 3, 5, 7, 9}
                       // v5 is now empty (valid but unspecified state)
  PrintVector(v5);
  PrintVector(v6);
}

int main() {
  DemonstrateVectorInitialization();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-11.cc && ./main
 *
 * 10 10 10 10 10
 * 1 2 3
 * 10 10 10 10 10
 * 1 3 5 7 9
 *
 * 1 3 5 7 9
 */