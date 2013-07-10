/*
 * Exercise 14.53: Given the definition of SmallInt on page 588, determine
 * whether the following addition expression is legal. If so, what addition
 * operator is used? If not, how might you change the code to make it legal?
 *     SmallInt s1;
 *     double d = s1 + 3.14;
 */

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout

/**
 * @class SmallInt
 * @brief Demonstrates conversion capabilities for overload resolution analysis
 */
class SmallInt {
  friend SmallInt operator+(const SmallInt& lhs, const SmallInt&) {
    std::cout << "SmallInt operator+(const SmallInt&, const SmallInt&) "
                 "called\n";
    return lhs;
  }

 public:
  /**
   * @brief Conversion constructor from int
   */
  SmallInt(int = 0) { std::cout << "SmallInt(int = 0) called\n"; }

  /**
   * @brief Conversion operator to int
   */
  operator int() const {
    std::cout << "SmallInt operator int() const called\n";
    return val;
  }

 private:
  std::size_t val;
};

/**
 * @struct LongDouble
 * @brief Demonstrates multiple conversion paths and operator overloads
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
    std::cout << "LongDouble operator double() called\n";
    return 0.0;
  }

  /**
   * @brief Conversion operator to float
   */
  operator float() {
    std::cout << "LongDouble operator float() called\n";
    return 0.0f;
  }

  /**
   * @brief Member operator+ for SmallInt addition
   */
  LongDouble operator+(const SmallInt&) {
    std::cout << "LongDouble operator+(const SmallInt&) called\n";
    return *this;
  }
};

/**
 * @brief Non-member operator+ for LongDouble and double
 */
LongDouble operator+(LongDouble& lhs, double) {
  std::cout << "LongDouble operator+(LongDouble&, double) called\n";
  return lhs;
}

int main() {
  SmallInt s1(5);  // Explicit initialization for clarity

  std::cout << "Attempting: double d = s1 + 3.14;\n";

  /*
   * This expression is ambiguous and will not compile because:
   * - Path A: Convert s1 to int (via operator int()), then convert int to
   *           double, use built-in operator+(double, double)
   * - Path B: Convert 3.14 to int (narrowing conversion), then convert int to
   *           SmallInt, use friend operator+(const SmallInt&, const SmallInt&)
   * - Path C: Convert 3.14 to SmallInt via conversion constructor,
   *           use friend operator+(const SmallInt&, const SmallInt&)
   * All paths require user-defined conversions and are considered equally
   * viable, resulting in compiler ambiguity error.
   */

  // To make it legal, provide explicit disambiguation:
  double d1 = static_cast<int>(s1) + 3.14;  // Explicit conversion path A
  std::cout << '\n';

  double d2 =
      s1 + SmallInt(3);  // Explicit conversion path B/C (note: narrowing)

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-53.cc && ./main
 * SmallInt(int = 0) called
 * Attempting: double d = s1 + 3.14;
 * SmallInt operator int() const called
 *
 * SmallInt(int = 0) called
 * SmallInt operator+(const SmallInt&, const SmallInt&) called
 * SmallInt operator int() const called
 */
