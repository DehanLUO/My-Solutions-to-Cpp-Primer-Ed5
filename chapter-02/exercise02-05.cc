/*
 * Exercise 2.5: Determine the type of each of the following literals. Explain
 * the differences among the literals in each of the four examples:
 *     (a) ’a’, L’a’, "a", L"a"
 *     (b) 10, 10u, 10L, 10uL, 012, 0xC
 *     (c) 3.14, 3.14f, 3.14L
 *     (d) 10, 10u, 10., 10e-2
 */

#include "../include/type_util.h"

int main() {
  PRINT_VAR_TYPE('a');   // char
  PRINT_VAR_TYPE(L'a');  // wchar_t
  PRINT_VAR_TYPE("a");   // char const*
  PRINT_VAR_TYPE(L"a");  // wchar_t const*

  PRINT_VAR_TYPE(10);    // int
  PRINT_VAR_TYPE(10u);   // unsigned int
  PRINT_VAR_TYPE(10L);   // long
  PRINT_VAR_TYPE(10uL);  // unsigned long
  PRINT_VAR_TYPE(012);   // int, octal
  PRINT_VAR_TYPE(0xC);   // int, hexadecimal

  PRINT_VAR_TYPE(3.14);   // double
  PRINT_VAR_TYPE(3.14f);  // float
  PRINT_VAR_TYPE(3.14L);  // long double

  PRINT_VAR_TYPE(10);     // int
  PRINT_VAR_TYPE(10u);    // unsigned int
  PRINT_VAR_TYPE(10.);    // double 10
  PRINT_VAR_TYPE(10e-2);  // double 0.1

  return 0;
}

/*
 * $ g++ -o main exercise02-05.cc && ./main
 * 'a' = a | type: char
 * L'a' = 97 | type: wchar_t
 * "a" = a | type: char const*
 * L"a" = 0x101883730 | type: wchar_t const*
 * 10 = 10 | type: int
 * 10u = 10 | type: unsigned int
 * 10L = 10 | type: long
 * 10uL = 10 | type: unsigned long
 * 012 = 10 | type: int
 * 0xC = 12 | type: int
 * 3.14 = 3.14 | type: double
 * 3.14f = 3.14 | type: float
 * 3.14L = 3.14 | type: long double
 * 10 = 10 | type: int
 * 10u = 10 | type: unsigned int
 * 10. = 10 | type: double
 * 10e-2 = 0.1 | type: double
 */