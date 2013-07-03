/*
 * Exercise 4.34: Given the variable definitions in this section, explain what
 * conversions take place in the following expressions:
 *     (a) if (fval)
 *     (b) dval = fval + ival;
 *     (c) dval + ival * cval;
 * Remember that you may need to consider the associativity of the operators.
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates implicit type conversions in expressions
 */
void DemonstrateConversions() {
  // The variable definitions in this section
  bool flag = false;
  char cval = 'a';
  short sval = -1;
  unsigned short usval = 2;
  int ival = -3;
  unsigned int uival = 4;
  long lval = -5;
  unsigned long ulval = 6;
  float fval = -7.F;
  double dval = 8.0;

  // Case (a): if (fval)
  // Conversion: float → bool (§4.11)
  // Rule: Arithmetic types convert to bool where 0 → false, else → true
  if (fval) {
    std::cout << "(a) fval converted to true (non-zero float)\n";
  }

  // Case (b): dval = fval + ival;
  // Conversions:
  //   1. int → float (ival promoted to float for + operation)
  //   2. float → double (assignment conversion)
  dval = fval + ival;
  std::cout << "(b) Result after conversions: " << dval << "\n";

  // Case (c): dval + ival * cval;
  // Conversions:
  //   1. char → int (cval promoted for multiplication)
  //   2. int → double (ival*cval result promoted for addition)
  double result = dval + ival * cval;
  std::cout << "(c) Result after conversions: " << result << "\n";
}

int main() {
  DemonstrateConversions();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-34.cc && ./main
 * (a) fval converted to true (non-zero float)
 * (b) Result after conversions: -10
 * (c) Result after conversions: -301
 */
