/*
 * Exercise 15.13: Given the following classes, explain each print function:
 *     class base {
 *      public:
 *       string name() { return basename; }
 *       virtual void print(ostream &os) { os << basename; }
 *
 *      private:
 *       string basename;
 *     };
 *     class derived : public base {
 *      public:
 *       void print(ostream &os) {
 *         print(os);
 *         os << " " << i;
 *       }
 *
 *      private:
 *       int i;
 *     };
 * If there is a problem in this code, how would you fix it?
 */

#ifndef CHAPTER_15_EXERCISE_13_H_
#define CHAPTER_15_EXERCISE_13_H_

#include <iostream>  // std::ostream, std::cout
#include <string>    // std::string

/**
 * @class Base
 * @brief Base class with virtual and non-virtual functions
 * @note Demonstrates polymorphic behavior through virtual functions
 */
class base {
 public:
  /**
   * @brief Default constructor
   */
  base() : basename("base") {}

  virtual ~base() = default;

  /**
   * @brief Non-virtual member function
   * @return basename string value
   * @note Uses static binding - determined at compile time
   */
  std::string name() {
    std::cout << "base::name() called\n";
    return basename;
  }

  /**
   * @brief Virtual print function for polymorphic output
   * @param os Output stream to write to
   * @note Virtual to enable derived class overrides
   */
  virtual void print(std::ostream &os) { os << "base::print(): " << basename; }

 private:
  std::string basename;
};

/**
 * @class Derived
 * @brief Derived class overriding base virtual function
 * @note Corrected version without recursion issue
 */
class derived : public base {
 public:
  /**
   * @brief Default constructor
   */
  derived() : i(42) {}
  /**
   * @brief Correct override of base print function
   * @param os Output stream to write to
   * @note  Properly calls base class version using scope resolution operator
   */
  void print(std::ostream &os) {
    // print(os);  // PROBLEM: Recursive call to itself instead of base class!
    base::print(os);  // FIX: Explicitly call base class version
    os << " | derived::print(): " << i;
  }

 private:
  int i;
};

#endif  // CHAPTER_15_EXERCISE_13_H_
