/*
 * Exercise 14.52: Which operator+, if any, is selected for each of the addition
 * expressions? List the candidate functions, the viable functions, and the type
 * conversions on the arguments for each viable function:
 *     struct LongDouble {
 *       // member operator+ for illustration purposes; + is usually a nonmember
 *       LongDouble operator+(const SmallInt&);
 *       // other members as in § 14.9.2 (p. 587)
 *     };
 *     LongDouble operator+(LongDouble&, double);
 *     SmallInt si;
 *     LongDouble ld;
 *     ld = si + ld;
 *     ld = ld + si;
 */

/*
 * ANALYSIS: ld = si + ld
 *
 * CANDIDATE FUNCTIONS:
 * 1. SmallInt operator+(const SmallInt&, const SmallInt&)
 * 2. LongDouble LongDouble::operator+(const SmallInt&)
 * 3. LongDouble operator+(LongDouble&, double)
 * 4. Built-in operator+(arithmetic types)
 *
 * VIABLE FUNCTIONS:
 * 1. SmallInt operator+(const SmallInt&, const SmallInt&)
 *    - First argument: si (exact match)
 *    - Second argument: ld → requires conversion
 *      Possible conversions for ld:
 *      a. ld → operator double() → double → SmallInt (user-defined + standard)
 *      b. ld → operator float() → float → SmallInt (user-defined + standard)
 *    - Requires user-defined conversion for second argument
 *
 * 2. Built-in operator+ for arithmetic types
 *    - Both arguments require conversion to arithmetic types
 *    - Many possible conversion combinations
 *    - All require multiple user-defined conversions
 *
 * PROBLEM: No exact match or good standard conversion sequence
 * The expression si + ld is AMBIGUOUS and will NOT compile!
 * Reason: Multiple conversion paths with no clear best match
 */

/*
 * ANALYSIS: ld = ld + si
 *
 * CANDIDATE FUNCTIONS:
 * 1. LongDouble LongDouble::operator+(const SmallInt&) [MEMBER]
 * 2. LongDouble operator+(LongDouble&, double) [NON-MEMBER]
 * 3. Built-in operator+(arithmetic types)
 *
 * VIABLE FUNCTIONS:
 * 1. LongDouble::operator+(const SmallInt&)
 *    - First argument: ld (exact match for implicit object)
 *    - Second argument: si → const SmallInt& (exact match)
 *    - Conversion sequence: NONE (exact matches)
 *    - Ranking: EXACT MATCH (best possible)
 *
 * 2. operator+(LongDouble&, double)
 *    - First argument: ld → LongDouble& (exact match)
 *    - Second argument: si → requires conversion to double
 *      Possible conversion: si → operator int() → int → double (user-defined +
 * standard)
 *    - Conversion sequence: User-defined + standard
 *    - Ranking: Worse than exact match
 *
 * 3. Built-in operator+ for arithmetic types
 *    - Both arguments require conversion
 *    - Multiple conversion paths possible
 *    - All require user-defined conversions
 *    - Ranking: Worse than member function
 *
 * RESULT: LongDouble::operator+(const SmallInt&) is selected
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
  SmallInt si;
  LongDouble ld;

  std::cout << '\n';

  // ld = si + ld;
  ld = ld + si;

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-52.cc && ./main
 * SmallInt(int = 0) called
 * LongDouble(double) constructor called
 *
 * LongDouble operator+(const SmallInt&) called
 */
