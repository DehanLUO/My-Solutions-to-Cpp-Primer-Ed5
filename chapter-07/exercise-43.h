/*
 * Exercise 7.43: Assume we have a class named NoDefault that has a constructor
 * that takes an int, but has no default constructor. Define a class C that has
 * a member of type NoDefault. Define the default constructor for C.
 */

#ifndef CHAPTER_07_EXERCISE_43_H_
#define CHAPTER_07_EXERCISE_43_H_

class NoDefault {
 public:
  /**
   * @brief Constructs NoDefault with specified value
   * @param val Initialization value
   */
  explicit NoDefault(int val) : value_(val) {}

  int GetValue() const { return value_; }

 private:
  int value_;
};

class C {
 public:
  /**
   * @brief Default constructs C with initialized NoDefault member
   * @note Uses in-class member initializer for NoDefault
   */
  C() : member_(42) {}  // Arbitrarily chosen default value

  /**
   * @brief Gets the NoDefault member's value
   * @return Current value of the member
   */
  int GetMemberValue() const { return member_.GetValue(); }

 private:
  NoDefault member_;
};

#endif  // CHAPTER_07_EXERCISE_43_H_
