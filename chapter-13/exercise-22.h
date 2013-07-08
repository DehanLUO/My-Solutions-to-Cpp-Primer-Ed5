/*
 * Exercise 13.22: Assume that we want HasPtr to behave like a value. That is,
 * each object should have its own copy of the string to which the objects
 * point. We’ll show the definitions of the copy-control members in the next
 * section. However, you already know everything you need to know to implement
 * these members. Write the HasPtr copy constructor and copy-assignment operator
 * before reading on.
 */

#ifndef CHAPTER_13_EXERCISE_22_H_
#define CHAPTER_13_EXERCISE_22_H_

#include <iostream>  // std::cout
#include <string>    // std::string

class HasPtr {
 public:
  /**
   * @brief Constructor - allocates a new string
   * @param s String to copy into dynamically allocated memory
   */
  HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}

  /**
   * @brief Copy constructor - performs deep copy
   * @param other HasPtr object to copy from
   */
  HasPtr(const HasPtr& other) : ps(new std::string(*other.ps)), i(other.i) {}

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

  /**
   * @brief Copy assignment operator
   * @param rhs HasPtr object to assign from
   * @return Reference to this object
   */
  HasPtr& operator=(const HasPtr& rhs) {
    // 1. Check for self-assignment
    if (this != &rhs) {
      // 2. Create new string before deleting old one (exception safety)
      std::string* temp_ps = new std::string(*rhs.ps);

      // 3. Delete old string
      delete ps;

      // 4. Copy data
      ps = temp_ps;
      i = rhs.i;
    }

    // 5. Return reference to this object
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
   * @brief Dereference operator (const version).
   * Provides read-only access to the underlying std::string.
   * @return Const reference to the std::string being pointed to.
   */
  std::string& operator*() { return *ps; }

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

#endif  // CHAPTER_13_EXERCISE_22_H_
