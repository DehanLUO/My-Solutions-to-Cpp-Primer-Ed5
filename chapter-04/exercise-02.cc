/*
 * Exercise 4.2: Using Table 4.12 (p. 166), parenthesize the following
 * expressions to indicate the order in which the operands are grouped:
 * (a) *vec.begin()
 * (b) *vec.begin() + 1
 */

#include <vector>  // std::vector

#include "../include/type_util.h"  // PRINT_VAR_TYPE

int main() {
  // Initialize test vector
  std::vector<int> vec = {0, 1, 2, 3, 4};

  /*
   * Part (a): Demonstrate *vec.begin() with explicit parentheses
   * Equvialent to *(vec.begin()) due to member acess having higher precedence
   */
  PRINT_VAR_TYPE(*vec.begin());

  /*
   * Part (b): Show *vec.begin() + 1 with explicit grouping
   * Equivalent to (*(vec.begin())) + 1 due to precedence rules
   */
  PRINT_VAR_TYPE(*(vec.begin() + 1));  // Output: second element

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-02.cc && ./main
 * *vec.begin(): 0 |type: int &
 * *(vec.begin() + 1): 1 |type: int &
 */