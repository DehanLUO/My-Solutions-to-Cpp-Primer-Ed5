/*
 * Exercise 2.9: Explain the following definitions. For those that are illegal,
 * explain what’s wrong and how to correct it.
 *     (a) std::cin >> int input_value;
 *     (b) int i = { 3.14 };
 *     (c) double salary = wage = 9999.99;
 *     (d) int i = 3.14;
 */

#include <iostream>  // std::cin

int main() {
  /*
   * (a) std::cin >> int input_value;
   * Illegal. The right-hand side of `>>` must be an existing object, not a
   * variable declaration.
   * Fix: Declare `input_value` first, then read into it.
   */
  int input_value;
  std::cin >> input_value;

  /*
   * (b) int i = { 3.14 };
   * Illegal. List initialization `{}` prohibits narrowing conversions. Type
   * `double` cannot be narrowed to `int` in initializer list.
   * Fix: Explicitly cast. Assigning (double)3.14 to (int)3 truncates the
   * farctional part.
   */
  int i_1 = {static_cast<int>(3.14)};

  /*
   * (c) double salary = wage = 9999.99;
   * Illegal. `wage` is undeclared. Multiple variables must be decalred with
   * commas, not chained assignments.
   * Fix: Declare `salary` and `wage` separately.
   */
  double salary = 9999.99, wage = salary;

  /*
   * (d) int i = 3.14;
   * Legal. Implicit conversion from `double` to `int` truncates 3.14 to 3,
   * losing precision (compiler warning).
   */
  int i_2 = 3.14;
}

/*
 * $ g++ -o main exercise-09.cc
 * exercise-09.cc:44:13: warning: implicit conversion from 'double' to 'int' changes value from 3.14 to 3 [-Wliteral-conversion]
 *    44 |   int i_2 = 3.14;
 *       |       ~~~   ^~~~
 * 1 warning generated.
 */
