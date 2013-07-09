/*
 * Exercise 14.4: Explain how to decide whether the following should be class
 * members:
 * (a) %    (b) %=   (c) ++   (d) ->   (e) <<   (f) &&   (g) ==   (h) ()
 */

#ifndef CHAPTER_14_EXERCISE_04_H_
#define CHAPTER_14_EXERCISE_04_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::istream, std::ostream

class MyClass {
 public:
  // Core special member functions
  MyClass();
  MyClass(const MyClass& other);
  MyClass(MyClass&& other) noexcept;
  ~MyClass();

  // --- Category 1: Mandatory Member Operators ---
  /*
   * These operators must be implemented as member functions because they:
   * 1. Directly manipulate the object's internal state
   * 2. Implement fundamental object behaviors
   * 3. Require access to private members
   */
  MyClass& operator=(
      const MyClass& rhs);  // Copy assignment (returns lvalue reference)
  MyClass& operator=(MyClass&& rhs) noexcept;      // Move assignment
  const int& operator[](std::size_t index) const;  // Const subscript access
  int& operator[](std::size_t index);              // Non-const subscript access
  void operator()() const;            // Function call operator (no parameters)
  MyClass* operator->();              // Member access operator
  const MyClass* operator->() const;  // Const member access operator

  // --- Category 2: Recommended Member Operators ---
  /*
   * Compound assignment operators are typically members because they:
   * 1. Modify the left operand directly
   * 2. Follow the assignment operator pattern
   * 3. Return references to support chaining
   */
  MyClass& operator+=(const MyClass& rhs);
  MyClass& operator-=(const MyClass& rhs);
  MyClass& operator*=(const MyClass& rhs);
  MyClass& operator/=(const MyClass& rhs);
  MyClass& operator%=(const MyClass& rhs);

  /*
   * Increment/decrement operators must be members because they:
   * 1. Modify the object's state
   * 2. Have special prefix/postfix syntax requirements
   */
  MyClass& operator++();    // Prefix increment
  MyClass operator++(int);  // Postfix increment (parameter as disambiguator)
  MyClass& operator--();    // Prefix decrement
  MyClass operator--(int);  // Postfix decrement

  // --- Category 3: Recommended Non-Member Operators ---
  /*
   * Symmetric arithmetic operators are implemented as non-member friends to:
   * 1. Allow implicit conversions on both operands
   * 2. Maintain consistent behavior with built-in types
   * 3. Support operator commutativity where applicable
   */
  friend MyClass operator+(const MyClass& lhs, const MyClass& rhs);
  friend MyClass operator-(const MyClass& lhs, const MyClass& rhs);
  friend MyClass operator*(const MyClass& lhs, double scalar);
  friend MyClass operator*(
      double scalar,
      const MyClass& rhs);  // Supports commutative multiplication
  friend MyClass operator/(const MyClass& lhs, double scalar);
  friend MyClass operator%(const MyClass& lhs, const MyClass& rhs);
  friend MyClass operator%(const MyClass& lhs, double scalar);

  /*
   * Comparison operators are non-member friends to:
   * 1. Enable symmetric comparison semantics
   * 2. Allow implicit conversions on either operand
   * 3. Maintain natural mathematical relationships
   */
  friend bool operator==(const MyClass& lhs, const MyClass& rhs);
  friend bool operator!=(const MyClass& lhs, const MyClass& rhs);
  friend bool operator<(const MyClass& lhs, const MyClass& rhs);
  friend bool operator>(const MyClass& lhs, const MyClass& rhs);
  friend bool operator<=(const MyClass& lhs, const MyClass& rhs);
  friend bool operator>=(const MyClass& lhs, const MyClass& rhs);

  /*
   * Logical AND is implemented as non-member but should be used cautiously
   * because:
   * 1. It loses short-circuit evaluation when overloaded
   * 2. Overloading logical operators is generally discouraged
   */
  friend bool operator&&(const MyClass& lhs, const MyClass& rhs);

  // --- Category 4: Stream Operators ---
  /*
   * I/O operators must be non-member functions because:
   * 1. The left operand is a stream object
   * 2. They require access to private members (hence friend)
   * 3. They return stream references for chaining
   */
  friend std::ostream& operator<<(std::ostream&, const MyClass&);
  friend std::istream& operator>>(std::istream&, MyClass&);

  // --- Category 5: Special Non-Member Utilities ---
  /*
   * swap is implemented as non-member friend to:
   * 1. Support Argument-Dependent Lookup (ADL)
   * 2. Enable efficient specialization
   * 3. Work with standard library algorithms
   */
  friend void swap(MyClass&, MyClass&);
};

#endif  // CHAPTER_14_EXERCISE_04_H_
