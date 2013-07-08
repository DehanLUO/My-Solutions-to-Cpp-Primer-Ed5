/*
 * Exercise 13.29: Explain why the calls to swap inside swap(HasPtr&, HasPtr&)
 * do not cause a recursion loop.
 */

/*
 * The swap implementation for HasPtr does not cause infinite recursion because:
 *
 * 1. Qualified Name Lookup:
 *    - When std::swap is called explicitly, it bypasses ADL (Argument-Dependent
 *      Lookup)
 *    - The compiler directly calls the standard library's std::swap template
 *    - This prevents any potential ambiguity with custom swap functions
 * 2. Template Specialization:
 *    - std::swap is a function template from the <utility> header
 *    - Each call to std::swap instantiates the template with concrete types
 *    - The template handles primitive types (pointers, ints) directly
 * 3. Member-wise Swapping:
 *    - The implementation swaps three primitive members:
 *      * ps_ (std::string*)
 *      * i_ (int)
 *      * use_ (std::size_t*)
 *    - These are all fundamental types with built-in swap operations
 * 4. No Indirect Invocation:
 *    - At no point does the implementation call swap(HasPtr&, HasPtr&)
 *    - Each member swap is handled by std::swap's primitive type
 *      specializations
 */

#ifndef CHAPTER_13_EXERCISE_29_H_
#define CHAPTER_13_EXERCISE_29_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout
#include <string>    // std::string
#include <utility>   // std::swap

/**
 * @brief Reference-counted string wrapper class
 *
 * Manages a dynamically allocated string with shared ownership semantics.
 * Implements proper copy control through reference counting.
 */
class HasPtr {
  friend void swap(HasPtr&, HasPtr&);

 public:
  /**
   * @brief Constructs a HasPtr managing a new string
   * @param s String to copy (default constructs empty string)
   * Time Complexity O(n) where n is string length
   * Space Complexity O(n) for string storage + sizeof(std::size_t)
   */
  HasPtr(const std::string& s = std::string())
      : ps_(new std::string(s)), use_(new std::size_t(1)) {}

  /**
   * @brief Copy constructor shares ownership
   * @param other HasPtr to copy from
   * Time Complexity O(1)
   * Space Complexity O(1)
   */
  HasPtr(const HasPtr& other) : ps_(other.ps_), i_(other.i_), use_(other.use_) {
    ++*use_;  // increment shared reference count
  }

  /**
   * @brief Destructor manages resource release
   * Time Complexity O(1)
   * Space Complexity O(1)
   */
  ~HasPtr() {
    /*
     * Decrement reference count and check if we're the last owner
     * This operation must be thread-safe in real implementations
     */
    if (0 != --*use_) return;

    // Free allocated memory
    delete ps_;
    delete use_;
  }

  /**
   * @brief Copy-assignment operator with strong exception safety
   * @param rhs HasPtr to assign from
   * @return Reference to this object
   * Time Complexity O(1)
   * Space Complexity O(1)
   */
  HasPtr& operator=(const HasPtr& rhs) {
    // Check for self-assignment
    if (this == &rhs) return *this;

    /*
     * Using increment-before-decrement for exception safety:
     * 1. First increment rhs's count
     * 2. Then decrement our count and possibly delete
     * 3. Finally copy pointers
     */
    ++*rhs.use_;
    if (0 == --*use_) {
      delete ps_;
      delete use_;
    }

    ps_ = rhs.ps_;
    i_ = rhs.i_;
    use_ = rhs.use_;

    // Return reference to this object
    return *this;
  }

  /**
   * @brief Copy assignment operator
   * @param rhs string object to assign from
   * @return Reference to this object
   * Time Complexity O(n) where n is string length
   * Space Complexity O(1)
   */
  HasPtr& operator=(const std::string& rhs) {
    *ps_ = rhs;  // Delegate to string's assignment
    return *this;
  }

  /**
   * @brief Dereference operator
   * @return Reference to managed string
   * Time Complexity O(1)
   */
  std::string& operator*() { return *ps_; }

  /**
   * @brief Const dereference operator
   * @return Const reference to managed string
   * Time Complexity O(1)
   */
  const std::string& operator*() const { return *ps_; }

  /**
   * @brief Gets current reference count
   * @return Number of shared owners
   * Time Complexity O(1)
   */
  std::size_t GetUse() const { return *use_; }

  /**
   * @brief Prints object state for demonstration
   */
  void Print() const {
    std::cout << "HasPtr @" << this << " {\n"
              << "  ps @" << ps_ << ": " << *ps_ << ",\n"
              << "  i: " << i_ << "\n"
              << "}\n";
  }

 private:
  std::string* ps_;   // Pointer to managed string
  int i_;             // Example int member
  std::size_t* use_;  // Pointer to shared reference count
};

/**
 * @brief Swaps two HasPtr objects and prints execution message
 * @param lhs First HasPtr to swap
 * @param rhs Second HasPtr to swap
 * Time Complexity O(1)
 * Space Complexity O(1)
 */
inline void swap(HasPtr& lhs, HasPtr& rhs) {
  std::swap(lhs.ps_, rhs.ps_);    // -> calls std::swap for pointers
  std::swap(lhs.i_, rhs.i_);      // -> calls std::swap for ints
  std::swap(lhs.use_, rhs.use_);  // -> calls std::swap for size_t pointers
  /*
   * At no point does this call chain circle back to swap(HasPtr&, HasPtr&)
   */
}

#endif  // CHAPTER_13_EXERCISE_29_H_
