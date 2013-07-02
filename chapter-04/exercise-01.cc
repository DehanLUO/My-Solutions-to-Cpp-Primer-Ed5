/*
 * Exercise 4.1: What is the value returned by 5 + 10 * 20 / 2?
 */

#include "../include/type_util.h"  // PRINT_VAR_TYPE

int main() {
  /*
   * 5 + 10 * 20 / 2 is equivalent to (5+ ((10 * 20) / 2)) = 105
   */
  decltype(5 + 10 * 20 / 2) num = 5 + 10 * 20 / 2;

  PRINT_VAR_TYPE(num);

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-01.cc && ./main
 * num: 105 |type: int
 */