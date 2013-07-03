// Exercise 6.2: Indicate which of the following functions are in error and why.
// Suggest how you might correct the problems.
//     (a) int f() {
//           string s;
//           // ...
//           return s;
//         }
//     (b) f2(int i) { /* . . . */ }
//     (c) int calc(int v1, int v1) /* . . . */ }
//.    (d) double square(double x) return x * x;

#include <iostream>  // std::cout
#include <string>    // std::string

// (a) Original problematic function:
// int f() {
//   string s;
//   // ...
//   return s;  // Error: returning string from int function
// }

/**
 * @brief Corrected version of function (a)
 * @return std::string The string value
 *
 * Changes:
 * 1. Changed return type to match returned value
 * 2. Added proper header include
 * 3. Added namespace qualification
 */
std::string CorrectedF() {
  std::string s;
  // ...
  return s;  // Now properly returns a string
}

// (b) Original problematic function:
// f2(int i) { /* . . . */ }  // Error: missing return type

/**
 * @brief Corrected version of function (b)
 * @param i Input integer
 * @return int Default return value
 *
 * Changes:
 * 1. Added void return type (or specific type if returning values)
 */
void CorrectedF2(int i) { /* . . . */ }  // void if no return needed
// OR if returning:
// int CorrectedF2(int i) { /* . . . */ return i; }

// (c) Original problematic function:
// int calc(int v1, int v1) /* . . . */ }  // Error: duplicate parameter names

/**
 * @brief Corrected version of function (c)
 * @param v1 First parameter
 * @param v2 Second parameter
 * @return int Calculation result
 *
 * Changes:
 * 1. Renamed second parameter to avoid duplication
 * 2. Added proper function body
 */
int CorrectedCalc(int v1, int v2) {
  return v1 + v2;  // Example implementation
}

// (d) Original problematic function:
// double square(double x) return x * x;  // Error: missing function body braces

/**
 * @brief Corrected version of function (d)
 * @param x Value to square
 * @return double Squared result
 *
 * Changes:
 * 1. Added proper function body delimiters
 */
double CorrectedSquare(double x) { return x * x; }

int main() {
  // Demonstration of corrected functions
  std::cout << CorrectedF() << '\n';
  CorrectedF2(42);
  std::cout << CorrectedCalc(3, 4) << '\n';
  std::cout << CorrectedSquare(3.5) << '\n';

  return 0;
}

/* $ g++ -o main chapter-06/exercise-01.cc && ./main
 *
 * 7
 * 12.25
 */
