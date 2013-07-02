/*
 * Exercise 3.34: Given that p1 and p2 point to elements in the same array, what
 * does the following code do? Are there values of p1 or p2 that make this code
 * illegal?
 *     p1 += p2 - p1;
 */

#include <iterator>  // std::begin, std::end

#include "../include/type_util.h"  // PRINT_VAR_TYPE

int main() {
  int arr[] = {10, 20, 30, 40};
  PRINT_VAR_TYPE(arr);
  PRINT_VAR_TYPE(&arr[0]);
  PRINT_VAR_TYPE(&arr[3]);

  auto *p1 = std::begin(arr);    // points to 10
  auto *p2 = std::end(arr) - 1;  // points to 40

  PRINT_VAR_TYPE(p1);
  PRINT_VAR_TYPE(p2);

  p1 += p2 - p1;  // now p1 points to 40 (same as p2)
  PRINT_VAR_TYPE(p1);

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-34.cc && ./main
 * arr: [10, 20, 30, 40] |type: int[4]
 * &arr[0]: (0x7ff7b7013c40) |type: int *
 * &arr[3]: (0x7ff7b7013c4c) |type: int *
 * p1: (0x7ff7b7013c40) |type: int *
 * p2: (0x7ff7b7013c4c) |type: int *
 * p1: (0x7ff7b7013c4c) |type: int *
 */