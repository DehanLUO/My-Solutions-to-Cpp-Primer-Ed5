/*
 * Exercise 3.44: Rewrite the programs from the previous exercises using a type
 * alias for the type of the loop control variables.
 */

#include <iostream>  // std::cout
#include <iterator>  // std::begin, std::end

#include "../include/type_util.h"  // PRINT_VAR_TYPE

using IntRow = const int[4];
using IntRowPtr = const int (*)[4];

int main() {
  int ia[3][4] = {
      // three elements; each element is an array of size 4
      {0, 1, 2, 3},   // initializers for the row indexed by 0
      {4, 5, 6, 7},   // initializers for the row indexed by 1
      {8, 9, 10, 11}  // initializers for the row indexed by 2
  };
  PRINT_VAR_TYPE(ia);

  // Range for
  {
    // Outer loop: each row (reference to int[4])
    for (const IntRow& row : ia) {
      // Inner loop: each element in row
      for (const int& col : row) {
        std::cout << col << ' ';
      }
    }
    std::cout << '\n';
  }

  // Ordinary for loop in one case using subscript
  {
    // Calculate row and column counts
    const size_t size_row = sizeof(ia) / sizeof(ia[0]);
    const size_t size_col = sizeof(ia[0]) / sizeof(ia[0][0]);

    // Traditional nested for loops with array indices
    for (size_t row = 0; row < size_row; ++row) {
      const IntRow& int_row = ia[row];
      for (size_t col = 0; col < size_col; ++col) {
        std::cout << int_row[col] << ' ';
      }
    }
    std::cout << '\n';
  }

  // Using pointers
  {
    // Pointer to end of row array
    const IntRowPtr pend_row = std::end(ia);

    // Iterate through rows using pointer arithmetic
    for (IntRowPtr p_row = std::begin(ia); p_row != pend_row; ++p_row) {
      // Pointer to end of current row's elements
      const int* const pend_col = std::end(*p_row);

      // Iterate through columns using pointer arithmetic
      for (const int* p_col = std::begin(*p_row); p_col != pend_col; ++p_col) {
        std::cout << *p_col << ' ';
      }
    }
    std::cout << '\n';
  }

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-44.cc && ./main
 * ia: [[0, 1, 2, 3], [4, 5, 6, 7], [8, 9, 10, 11]] |type: int[3][4]
 * 0 1 2 3 4 5 6 7 8 9 10 11
 * 0 1 2 3 4 5 6 7 8 9 10 11
 * 0 1 2 3 4 5 6 7 8 9 10 11
 */
