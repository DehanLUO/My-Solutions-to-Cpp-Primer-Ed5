/*
 * Exercise 4.35: Given the following definitions,
 *     char cval;
 *     int ival;
 *     unsigned int ui;
 *     float fval;
 *     double dval;
 * identify the implicit type conversions, if any, taking place:
 *     (a) cval = ’a’ + 3;
 *     (b) fval = ui - ival * 1.0;
 *     (c) dval = ui * fval;
 *     (d) cval = ival + fval + dval;
 */

#include <iostream>  // std::cout

#include "../include/type_util.h"  // PRINT_VAR_TYPE

/**
 * @brief Demonstrates implicit type conversions in various expressions
 */
void DemonstrateConversions() {
  // Variable definitions per exercise prompt
  char cval = 'a';
  int ival = 42;
  unsigned int ui = 10;
  float fval = 3.14f;
  double dval = 2.71828;

  // Expression (a): cval = 'a' + 3;
  // Conversions:
  //   1. 'a' (char) promoted to int for addition
  //   2. Result (int) converted back to char for assignment
  cval = 'a' + 3;
  PRINT_VAR_TYPE('a' + 3);
  std::cout << "(a) char result: " << cval << " (ASCII "
            << static_cast<int>(cval) << ")\n";

  // Expression (b): fval = ui - ival * 1.0;
  // Conversions:
  //   1. ival converted to double for multiplication
  //   2. ui converted to double for subtraction
  //   3. Result (double) converted to float for assignment
  fval = ui - ival * 1.0;
  PRINT_VAR_TYPE(ival * 1.0);
  PRINT_VAR_TYPE(ui - ival * 1.0);
  std::cout << "(b) float result: " << fval << "\n";

  // Expression (c): dval = ui * fval;
  // Conversions:
  //   1. ui converted to float for multiplication
  //   2. Result (float) converted to double for assignment
  dval = ui * fval;
  PRINT_VAR_TYPE(ui * fval);
  std::cout << "(c) double result: " << dval << "\n";

  // Expression (d): cval = ival + fval + dval;
  // Conversions:
  //   1. ival converted to float for addition with fval
  //   2. Result (float) converted to double for addition with dval
  //   3. Final result (double) converted to char for assignment
  cval = ival + fval + dval;
  PRINT_VAR_TYPE(ival + fval + dval);
  std::cout << "(d) char result: " << cval << " (ASCII "
            << static_cast<int>(cval) << ")\n";
}

int main() {
  DemonstrateConversions();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-35.cc && ./main
 * 'a' + 3: 100 |type: int
 * (a) char result: d (ASCII 100)
 * ival * 1.0: 42 |type: double
 * ui - ival * 1.0: -32 |type: double
 * (b) float result: -32
 * ui * fval: -320 |type: float
 * (c) double result: -320
 * ival + fval + dval: -310 |type: double
 * (d) char result: � (ASCII -54)
 */
