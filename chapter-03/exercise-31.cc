/*
 * Exercise 3.31: Write a program to define an array of ten ints. Give each
 * element the same value as its position in the array.
 */

#include "../include/type_util.h"  // PRINT_VAR_TYPE

constexpr uint8_t kArrSize = 10;  // Fixed array size (10 elements)

int main() {
  // Declare an array of 16-bit unsigned integers with size kArrSize
  uint16_t arr[kArrSize];

  // Loop through each element of the array
  for (uint16_t idx = 0; idx < kArrSize; ++idx) {
    arr[idx] = idx;  // Assign the current index value to the array element
  }

  PRINT_VAR_TYPE(arr);

  return 0;  // Indicate successful
}

/*
 * $ g++ -o main chapter-03/exercise-31.cc
 * arr: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9] |type: (unsigned short)[10]
 */