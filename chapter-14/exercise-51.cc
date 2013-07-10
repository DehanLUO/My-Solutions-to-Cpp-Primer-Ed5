/*
 * Exercise 14.51: Show the conversion sequences (if any) needed to call each
 * version of calc and explain why the best viable function is selected.
 *     void calc(int);
 *     void calc(LongDouble);
 *     double dval;
 *     calc(dval);  // which calc?
 */

/*
 * For calc(int) overload:
 * Conversion sequence: double → int
 *  - Ranking: Standard Conversion
 *  - Type: double → int is floating-integral conversion
 *
 * For calc(LongDouble) overload:
 * Conversion sequence: double → LongDouble
 *  - Ranking: User-defined Conversion
 *  - Type: User-defined conversion via constructor
 *
 * OVERLOAD RESOLUTION PRIORITY:
 * 1. Exact match (no conversion needed)
 * 2. Promotion (e.g., float → double)
 * 3. Standard conversion (e.g., int → double)
 * 4. User-defined conversion
 * 5. Ellipsis conversion (...)
 *
 * DETAILED COMPARISON:
 * calc(int) requires: double → int
 *  - This is a floating-point to integral conversion
 *  - Considered a 'bad' standard conversion (potential data loss)
 * calc(LongDouble) requires: double → LongDouble
 *  - This uses LongDouble's conversion constructor
 *  - Considered a user-defined conversion
 *
 * Therefore: calc(int) is selected because it uses
 * a standard conversion, even though it's a 'bad' one!
 */

#include <iostream>  // std::cout

/**
 * @struct LongDouble
 * @brief Demonstrates conversion sequences in overload resolution
 */
struct LongDouble {
  /**
   * @brief Conversion constructor from double
   */
  LongDouble(double = 0.0) {
    std::cout << "LongDouble(double) constructor called\n";
  }

  /**
   * @brief Conversion operator to double
   */
  operator double() {
    std::cout << "operator double() called\n";
    return 0.0;
  }

  /**
   * @brief Conversion operator to float
   */
  operator float() {
    std::cout << "operator float() called\n";
    return 0.0f;
  }
};

/**
 * @brief First overload: takes int parameter
 */
void calc(int) { std::cout << "calc(int) called\n"; }

/**
 * @brief Second overload: takes LongDouble parameter
 */
void calc(LongDouble) { std::cout << "calc(LongDouble) called\n"; }

/**
 * @brief Main function demonstrating overload resolution
 * @return int Exit status code (0 for success)
 */
int main() {
  double dval = 3.14;

  // calling calc(dval) with dval
  calc(dval);

  std::cout << "\n";
  // to force calc(LongDouble) instead:
  calc(static_cast<LongDouble>(dval));

  std::cout << "\n";
  // Or using explicit constructor call
  calc(LongDouble(dval));

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-51.cc && ./main
 * calc(int) called
 *
 * LongDouble(double) constructor called
 * calc(LongDouble) called
 *
 * LongDouble(double) constructor called
 * calc(LongDouble) called
 */
