/*
 * Exercise 7.54: Should the members of Debug that begin with set_ be declared
 * as constexpr? If not, why not?
 */

#ifndef CHAPTER_07_EXERCISE_54_H_
#define CHAPTER_07_EXERCISE_54_H_

class Debug {
 public:
  /**
   * @brief Default constructor enables all flags
   * @param b Initial value for all flags (default true)
   */
  constexpr Debug(bool b = true) : hw(b), io(b), other(b) {}

  /**
   * @brief Full constructor sets individual flags
   * @param h Hardware error flag
   * @param i I/O error flag
   * @param o Other errors flag
   */
  constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}

  /**
   * @brief Checks if any error flag is set
   * @return True if any flag is true
   */
  constexpr bool any() const noexcept { return hw || io || other; }

  /*
   * 1. Single-statement restriction
   *    - constexpr function body must be = delete, = default,
   *      or a single return statement
   *    - Setters require assignment statements (disqualified)
   *
   * 2. Compile-time immutability
   *    - Constant expressions cannot modify objects
   *    - Object modification is runtime operation
   *
   * 3. Literal type requirements
   *    - constexpr functions must return literal types
   *    - void-returning setters can't satisfy this
   */
  void set_io(bool b) { io = b; }
  void set_hw(bool b) { hw = b; }
  void set_other(bool b) { other = b; }

 private:
  bool hw;     // hardware errors
  bool io;     // I/O errors
  bool other;  // other errors
};

#endif  // CHAPTER_07_EXERCISE_54_H_