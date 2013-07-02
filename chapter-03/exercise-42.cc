/*
 * Exercise 3.42: Write a program to copy a vector of ints into an array of
 * ints.
 */

#include <algorithm>  // std::copy
#include <iostream>   // std::cerr
#include <iterator>   // std::begin
#include <vector>     // std::vector

#include "../include/type_util.h"  // PRINT_VAR_TYPE

int main() {
  // Source vector
  std::vector<int> vec_scores = {1, 2, 3, 4, 5};

  // Ensure vector is not too big
  constexpr size_t max_array_size = 10;
  if (vec_scores.size() > max_array_size) {
    std::cerr << "Error: Vector too large for our array.\n";
    return -1;
  }

  // Method 1: Manual copy
  {
    // Create destination array
    int arr_scores[max_array_size] = {};  // Zero-initialized

    for (size_t idx = 0; idx < vec_scores.size(); ++idx) {
      arr_scores[idx] = vec_scores[idx];
    }

    PRINT_VAR_TYPE(arr_scores);
  }

  // Method 2: std::copy
  {
    // Create destination array
    int arr_scores[max_array_size] = {};  // Zero-initialized

    std::copy(vec_scores.begin(), vec_scores.end(), std::begin(arr_scores));

    PRINT_VAR_TYPE(arr_scores);
  }

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-42.cc && ./main
 * arr_scores: [1, 2, 3, 4, 5, 0, 0, 0, 0, 0] |type: int[10]
 * arr_scores: [1, 2, 3, 4, 5, 0, 0, 0, 0, 0] |type: int[10]
 */