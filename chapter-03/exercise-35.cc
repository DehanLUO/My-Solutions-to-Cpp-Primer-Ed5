/*
 * Exercise 3.35: Using pointers, write a program to set the elements in an
 * array to zero.
 */

#include <iterator>  // std::begin, std::end

#include "../include/type_util.h"  // PRINT_VAR_TYPE

int main() {
  int arr[] = {10, 20, 30, 40};  // Initialize the test array
  PRINT_VAR_TYPE(arr);

  // Get pointer to end (one past last element)
  auto *pend = std::end(arr);
  // Loop through array using pointer arithmetic
  for (auto *p = std::begin(arr); p != pend; ++p) {
    *p = 0;  // Zero out current element
  }

  PRINT_VAR_TYPE(arr);  // Verify

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-34.cc && ./main
 * arr: [10, 20, 30, 40] |type: int[4]
 * arr: [0, 0, 0, 0] |type: int[4]
 */