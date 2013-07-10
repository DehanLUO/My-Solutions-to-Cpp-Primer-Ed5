/*
 * Exercise 14.35: Write a class like PrintString that reads a line of input
 * from an istream and returns a string representing what was read. If the read
 * fails, return the empty string.
 */

#ifndef CHAPTER_14_EXERCISE_35_H_
#define CHAPTER_14_EXERCISE_35_H_

#include <iostream>  // std::istream, std::getline
#include <string>    // std::string

/**
 * @class ReadString
 * @brief Functor class that reads a line from an input stream
 *
 * This class provides a function object that reads a line from the specified
 * input stream and returns the result as a string. If the read operation fails,
 * it returns an empty string.
 */
class ReadString {
 public:
  /**
   * @brief Constructs a ReadString object with specified input stream
   * @param istream Reference to input stream (defaults to std::cin)
   */
  explicit ReadString(std::istream& istream = std::cin) : istream_(istream) {}

  /**
   * @brief Function call operator that performs the line reading operation
   * @return std::string The read line or empty string on failure
   * @time Complexity O(n) where n is the length of the input line
   * @space Complexity O(n) for storing the read line
   */
  std::string operator()() {
    std::string line;
    if (!std::getline(istream_, line)) {
      line.clear();
    }
    return line;
  }

 private:
  std::istream&
      istream_;  // Reference to the input stream for reading operations
};

#endif  // CHAPTER_14_EXERCISE_35_H_
