/*
 * Exercise 2.33: Using the variable definitions from this section, determine
 * what happens in each of these assignments:
 *     a = 42;     b = 42;     c = 42;
 *     d = 42;     e= 42;      g = 42;
 */

#include "../include/type_util.h"

int main() {
  // variable definitions from section 2.5.2 (The auto Type Specifier)
  int i = 0, &r = i;
  auto a = r;  // a is an int (r is an alias for i, which has type int)
  const int ci = i, &cr = ci;
  auto b = ci;   // b is an int(top-level const in ci is dropped)
  auto c = cr;   // c is an int(cr is an alias for ci whose const is top-level)
  auto d = &i;   // d is an int* (& of an int object is int*)
  auto e = &ci;  // e is const int* (& of a const object is low-level const)
  const auto f = ci;  // deduced type of ci is int; f has type const int
  auto &g = ci;       // g is a const int& that is bound to ci;

  PRINT_VAR_TYPE(a);  // int
  PRINT_VAR_TYPE(b);  // int
  PRINT_VAR_TYPE(c);  // int
  PRINT_VAR_TYPE(d);  // int*
  PRINT_VAR_TYPE(e);  // int const *
  PRINT_VAR_TYPE(f);  // int const
  PRINT_VAR_TYPE(g);  // int const &

  a = 42;
  b = 42;
  c = 42;
  // d = 42;  // Illegal. `d` is a pointer to int
  // e = 42;  // Illegal. `e` is a const-int
  // g = 42;  // Illegal. `g` is a reference to const int

  return 0;
}

/*
 * $ g++ -o main exercise02-33.cc && ./main
 * a: 0|type: int
 * b: 0|type: int
 * c: 0|type: int
 * d: 0x7ff7bb7b3f88|type: int *
 * e: 0x7ff7bb7b3f78|type: int const *
 * f: 0|type: int const
 * g: 0|type: int const &
 */