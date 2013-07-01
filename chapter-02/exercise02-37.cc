/*
 * Exercise 2.37: Assignment is an example of an expression that yields a
 * reference type. The type is a reference to the type of the left-hand operand.
 * That is, if i is an int, then the type of the expression i = x is int&. Using
 * that knowledge, determine the type and value of each variable in this code:
 *     int a = 3, b = 4;
 *     decltype(a) c = a;
 *     decltype(a = b) d = a;
 */

#include "../include/type_util.h"

int main() {
  int a = 3, b = 4;
  decltype(a) c = a;
  decltype(a = b) d = a;

  PRINT_VAR_TYPE(a);  // int, 3
  PRINT_VAR_TYPE(b);  // int, 4
  PRINT_VAR_TYPE(c);  // int, 3
  PRINT_VAR_TYPE(d);  // int &, 3

  return 0;
}

/*
 * $ g++ -o main exercise02-37.cc && ./main
 * exercise02-37.cc:16:14: warning: expression with side effects has no effect in an unevaluated context [-Wunevaluated-expression]
 *    16 |   decltype(a = b) d = a;
 *       |              ^
 * 1 warning generated.
 * a: 3|type: int
 * b: 4|type: int
 * c: 3|type: int
 * d: 3|type: int &
 */