/*
 * Exercise 2.36: In the following code, determine the type of each variable and
 * the value each variable has when the code finishes:
 *     int a = 3, b = 4;
 *     decltype(a) c = a;
 *     decltype((b)) d = a;
 *     ++c;
 *     ++d;
 */

#include "../include/type_util.h"

int main() {
  int a = 3, b = 4;
  decltype(a) c = a;
  decltype((b)) d = a;
  ++c;
  ++d;

  PRINT_VAR_TYPE(a);  // int, 4
  PRINT_VAR_TYPE(b);  // int, 4
  PRINT_VAR_TYPE(c);  // int, 4
  PRINT_VAR_TYPE(d);  // int &, 4
  return 0;
}

/*
 * $ g++ -o main exercise-36.cc && ./main
 * a=4 |type: int
 * b=4 |type: int
 * c=4 |type: int
 * d=4 |type: int &
 */