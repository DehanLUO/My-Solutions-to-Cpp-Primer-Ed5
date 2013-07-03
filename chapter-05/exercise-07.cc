/*
 * Exercise 5.7: Correct the errors in each of the following code fragments:
 *     (a) if (ival1 != ival2)
 *           ival1 = ival2
 *         else ival1 = ival2 = 0;
 *     (b) if (ival < minval)
 *           minval = ival;
 *           occurs = 1;
 *     (c) if (int ival = get_value())
 *           cout << "ival = " << ival << endl;
 *         if (!ival)
 *           cout << "ival = 0\n";
 *     (d) if (ival = 0)
 *           ival = get_value()
 */

#include <iostream>  // std::cout

int get_value() { return 42; }  // Dummy function for demonstration

int main() {
  // Fragment (a) Corrections:
  int ival1, ival2;
  if (ival1 != ival2) {
    ival1 = ival2;  // Added semicolon
  } else {          // Added braces for clarity
    ival1 = ival2 = 0;
  }

  // Fragment (b) Corrections:
  int ival, minval, occurs;
  if (ival < minval) {  // Added braces to include both statements
    minval = ival;
    occurs = 1;
  }

  // Fragment (c) Corrections:
  if (int ival = get_value()) {
    std::cout << "ival = " << ival << std::endl;
  } else {  // Changed to else-if for same variable
    std::cout << "ival = 0\n";
  }

  // Fragment (d) Corrections:
  int ival3;
  if (ival3 == 0) {       // Changed = to == for comparison
    ival3 = get_value();  // Added semicolon
  }

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-07.cc && ./main
 * ival = 42
 */
