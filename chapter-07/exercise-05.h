/*
 * Exercise 7.5: Provide operations in your Person class to return the name and
 * address. Should these functions be const? Explain your choice.
 */

#ifndef CHAPTER_07_EXERCISE_05_H_
#define CHAPTER_07_EXERCISE_05_H_

#include <string>  // std::string

struct Person {
  std::string name;
  std::string address;

  /**
   * @brief Retrieves the person's name
   * @return Copy of the name string
   * @note Marked const as it doesn't modify object state
   */
  std::string GetName() const;

  /**
   * @brief Retrieves the person's address
   * @return Copy of the address string
   * @note Marked const as it doesn't modify object state
   */
  std::string GetAddress() const;
};

/*
 * Accessor method implementations:
 * 1. Return copies to preserve encapsulation
 * 2. Const-qualified to enable use on const objects
 * 3. Minimal implementation for efficiency
 */
std::string Person::GetName() const { return name; }

std::string Person::GetAddress() const { return address; }

#endif  // CHAPTER_07_EXERCISE_05_H_
