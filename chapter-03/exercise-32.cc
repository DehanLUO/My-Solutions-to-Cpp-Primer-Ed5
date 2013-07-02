/*
 * Exercise 3.32: Copy the array you defined in the previous exercise into
 * another array. Rewrite your program to use vectors.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

#include "../include/type_util.h"  // PRINT_VAR_TYPE

constexpr uint8_t kArrSize = 10;  // Fixed array size (10 elements)

int main() {
  /*
   * Original array initialization
   */
  uint16_t arr[kArrSize];
  for (uint16_t idx = 0; idx < kArrSize; ++idx) {
    arr[idx] = idx;
  }

  /*
   * Array-to-array copy
   */
  uint16_t dest_arr[kArrSize];  // Destination array
  for (uint16_t idx = 0; idx < kArrSize; ++idx)
    dest_arr[idx] = arr[idx];  // Element-wise copy

  PRINT_VAR_TYPE(dest_arr);

  /*
   * vector copy
   */
  std::vector<uint16_t> uvec;  // Create empty vector
  for (uint16_t idx = 0; idx < kArrSize; ++idx)
    uvec.emplace_back(arr[idx]);  // Copy elements

  // Print vector contents
  for (const auto& num : uvec) std::cout << num << ' ';
  std::cout << '\n';

  return 0;  // Indicate successful
}

/*
 * $ g++ -o main chapter-03/exercise-3w.cc
 * dest_arr: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9] |type: (unsigned short)[10]
 * 0 1 2 3 4 5 6 7 8 9
 */