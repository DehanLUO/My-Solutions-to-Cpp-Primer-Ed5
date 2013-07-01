/*
 * Exercise 2.34: Write a program containing the variables and assignments from
 * the previous exercise. Print the variables before and after the assignments
 * to check whether your predictions in the previous exercise were correct. If
 * not, study the examples until you can convince yourself you know what led you
 * to the wrong conclusion.
 */

#include "../include/type_util.h"

int main() {
  // variable definitions from section 2.5.2 (The auto Type Specifier)
  int i = 0, &r = i;
  auto a = r;  // a is an int (r is an alias for i, which has type int)
  const int ci = i, &cr = ci;
  auto b = ci;   // b is an int (top-level const in ci is dropped)
  auto c = cr;   // c is an int (cr is an alias for ci whose const is top-level)
  auto d = &i;   // d is an int* (& of an int object is int*)
  auto e = &ci;  // e is const int* (& of a const object is low-level const)
  auto &g = ci;  // g is a const int& that is bound to ci;

  a = 42;
  PRINT_VAR_TYPE(a);  // int

  b = 42;
  PRINT_VAR_TYPE(b);  // int

  c = 42;
  PRINT_VAR_TYPE(c);  // int
  // d = 42;  // Illegal. `d` is a pointer to int
  // e = 42;  // Illegal. `e` is a const-int
  // g = 42;  // Illegal. `g` is a reference to const int

  PRINT_VAR_TYPE(i);   // int
  PRINT_VAR_TYPE(r);   // int &
  PRINT_VAR_TYPE(ci);  // int const
  PRINT_VAR_TYPE(cr);  // int const &

  return 0;
}

/*
 * $ g++ -o main exercise02-34.cc && ./main
 * a: 42|type: int
 * b: 42|type: int
 * c: 42|type: int
 * i: 0|type: int
 * r: 0|type: int &
 * ci: 0|type: int const
 * cr: 0|type: int const &
 */