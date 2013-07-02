/*
 * Exercise 3.36: Write a program to compare two arrays for equality. Write a
 * similar program to compare two vectors.
 */

#include <ios>       // std::boolalpha
#include <iostream>  // std::cout
#include <iterator>  // std::begin, std::end
#include <vector>    // std::vector

bool CompareArrays(const int* source, const int* target, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (source[i] != target[i]) return false;
  }
  return true;
}

int main() {
  /*
   * Compare two arrays
   */
  {
    int arr1[] = {1, 2, 3};
    int arr2[] = {1, 2, 3};
    int arr3[] = {1, 2, 4};

    // Compare sizes first (arrays decay to pointers, so we need to track size)
    size_t size1 = std::end(arr1) - std::begin(arr1);
    size_t size2 = std::end(arr2) - std::begin(arr2);

    bool result = (size1 == size2) && CompareArrays(arr1, arr2, size1);
    std::cout << std::boolalpha << "arr1 == arr2: " << result << '\n';

    size_t size3 = std::end(arr3) - std::begin(arr3);
    result = (size1 == size3) && CompareArrays(arr1, arr3, size1);
    std::cout << "arr1 == arr3: " << result << '\n';
  }

  /*
   * Compare two vectors
   */
  {
    std::vector<int> ivec1(4, 1);
    std::vector<int> ivec2{1, 1, 1, 1};
    std::vector<int> ivec3(4);

    std::cout << "ivec1 == ivec2: " << (ivec1 == ivec2) << '\n';
    std::cout << "ivec1 == ivec3: " << (ivec1 == ivec3) << '\n';
  }

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-36.cc && ./main
 * arr1 == arr2: true
 * arr1 == arr3: false
 * ivec1 == ivec2: true
 * ivec1 == ivec3: false
 */