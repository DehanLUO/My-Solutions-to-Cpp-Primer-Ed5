/*
 * Exercise 3.45: Rewrite the programs again, this time using auto.
 */

#include <iostream>  // std::cout
#include <iterator>  // std::begin, std::end

#include "../include/type_util.h"  // PRINT_VAR_TYPE

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
    for (const auto& row : ia) {
      // Inner loop: each element in row
      for (const auto& col : row) {
        std::cout << col << ' ';
      }
    }
    std::cout << '\n';
  }

  // Ordinary for loop in one case using subscript
  {
    // Calculate row and column counts
    const auto size_row = sizeof(ia) / sizeof(ia[0]);
    const auto size_col = sizeof(ia[0]) / sizeof(ia[0][0]);

    // Traditional nested for loops with array indices
    for (decltype(size_row + 0) row = 0; row < size_row; ++row) {
      const auto& int_row = ia[row];
      for (decltype(size_col + 0) col = 0; col < size_col; ++col) {
        std::cout << int_row[col] << ' ';
      }
    }
    std::cout << '\n';
  }

  // Using pointers
  {
    // Pointer to end of row array
    const auto* pend_row = std::end(ia);

    // Iterate through rows using pointer arithmetic
    for (auto* p_row = std::begin(ia); p_row != pend_row; ++p_row) {
      // Pointer to end of current row's elements
      auto* pend_col = std::end(*p_row);

      // Iterate through columns using pointer arithmetic
      for (auto* p_col = std::begin(*p_row); p_col != pend_col; ++p_col) {
        std::cout << *p_col << ' ';
      }
    }
    std::cout << '\n';
  }

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-45.cc && ./main
 * ia: [[0, 1, 2, 3], [4, 5, 6, 7], [8, 9, 10, 11]] |type: int[3][4]
 * 0 1 2 3 4 5 6 7 8 9 10 11
 * 0 1 2 3 4 5 6 7 8 9 10 11
 * 0 1 2 3 4 5 6 7 8 9 10 11
 */
