/*
 * Exercise 2.38: Describe the differences in type deduction between decltype
 * and auto. Give an example of an expression where auto and decltype will
 * deduce the same type and an example where they will deduce differing types.
 */

/*
 * `auto`: Generally strips off references and top-level const. Deduces the
 * value type of the initializer expression.
 * `decltype`: Yields the exact type, including reference and const qualifiers,
 * as is from the expression.
 */

#include "../include/type_util.h"

int main() {
  // same type deduction
  int variable = 9527;
  auto variable_auto = variable;
  decltype(variable) variable_decltype = variable;
  PRINT_VAR_TYPE(variable_auto);      // int, 9527
  PRINT_VAR_TYPE(variable_decltype);  // int, 9527

  // different type deduction
  int& reference = variable;
  auto reference_auto = reference;
  decltype(reference) reference_decltype = reference;
  PRINT_VAR_TYPE(reference_auto);      // int, 9527
  PRINT_VAR_TYPE(reference_decltype);  // int &, 9527

  return 0;
}

/*
 * $ g++ -o main exercise-38.cc && ./main
 * variable_auto=9527 |type: int
 * variable_decltype=9527 |type: int
 * reference_auto=9527 |type: int
 * reference_decltype=9527 |type: int &
 */