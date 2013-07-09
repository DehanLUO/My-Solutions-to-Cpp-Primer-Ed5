/*
 * Exercise 13.52: Explain in detail what happens in the assignments of the
 * HasPtr objects on page 541. In particular, describe step by step what happens
 * to values of hp, hp2, and of the rhs parameter in the HasPtr assignment
 * operator.
 */

#ifndef CHAPTER_13_EXERCISE_52_H_
#define CHAPTER_13_EXERCISE_52_H_

#include <iostream>  // std::cout
#include <string>    // std::string

class HasPtr {
  friend void swap(HasPtr&, HasPtr&);  // For exercise-30

 public:
  /**
   * @brief Constructor - allocates a new string
   * @param s String to copy into dynamically allocated memory
   */
  HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {
    std::cout << "HasPtr(const std::string& s = std::string())\n";
  }

  /**
   * @brief Copy constructor - performs deep copy
   * @param other HasPtr object to copy from
   */
  HasPtr(const HasPtr& other) : ps(new std::string(*other.ps)), i(other.i) {
    std::cout << "HasPtr(const HasPtr& other):" << *other.ps << "\n";
  }

  HasPtr(HasPtr&& other) noexcept : ps(other.ps), i(other.i) {
    std::cout << "HasPtr(HasPtr&& other) noexcept:" << *other.ps << "\n";
    other.ps = nullptr;
  }

  /**
   * @brief Destructor - frees allocated memory
   *
   * Key features:
   * 1. Releases the dynamically allocated string
   * 2. Marked noexcept as destructors shouldn't throw
   * 3. Handles case where ps might be nullptr
   */
  ~HasPtr() {
    delete ps;  // Free allocated memory
  }

  // /**
  //  * @brief Copy assignment operator
  //  * @param rhs HasPtr object to assign from
  //  * @return Reference to this object
  //  */
  // HasPtr& operator=(const HasPtr& rhs) {
  //   // 1. Check for self-assignment
  //   if (this != &rhs) {
  //     // 2. Create new string before deleting old one (exception safety)
  //     std::string* temp_ps = new std::string(*rhs.ps);
  //
  //     // 3. Delete old string
  //     delete ps;
  //
  //     // 4. Copy data
  //     ps = temp_ps;
  //     i = rhs.i;
  //   }
  //
  //   // 5. Return reference to this object
  //   return *this;
  // }

  HasPtr& operator=(HasPtr rhs) {
    std::cout << "HasPtr& operator=(HasPtr rhs)" << *rhs.ps << "\n";
    swap(*this, rhs);
    return *this;
  }

  /**
   * @brief Copy assignment operator
   * @param rhs string object to assign from
   * @return Reference to this object
   */
  HasPtr& operator=(const std::string& rhs) {
    *ps = rhs;
    return *this;
  }

  /**
   * @brief Less-than comparison operator
   * @param rhs Right-hand side HasPtr to compare with
   * @return true if this string is less than rhs's string
   */
  bool operator<(const HasPtr& rhs) const { return *ps < *rhs.ps; }

  /**
   * @brief Dereference operator
   * Provides access to the underlying std::string.
   * @return Reference to the std::string being pointed to.
   */
  std::string& operator*() { return *ps; }

  /**
   * @brief Dereference operator (const version).
   * Provides read-only access to the underlying std::string.
   * @return Const reference to the std::string being pointed to.
   */
  const std::string& operator*() const { return *ps; }

  /**
   * @brief Prints object state for demonstration
   */
  void Print() const {
    std::cout << "HasPtr @" << this << " {\n"
              << "  ps @" << ps << ": " << *ps << ",\n"
              << "  i: " << i << "\n"
              << "}\n";
  }

 private:
  std::string* ps;
  int i;
};

/**
 * @brief Swaps two HasPtr objects and prints execution message
 * @param lhs First HasPtr to swap
 * @param rhs Second HasPtr to swap
 * @Time Complexity O(1)
 * @Space Complexity O(1)
 */
inline void swap(HasPtr& lhs, HasPtr& rhs) {
  std::cout << "==> Executing swap between \"" << *lhs << "\" and \"" << *rhs
            << "\"\n";

  std::swap(lhs.ps, rhs.ps);  // Swap string pointers
  std::swap(lhs.i, rhs.i);    // Swap integer members
}

#endif  // CHAPTER_13_EXERCISE_52_H_
