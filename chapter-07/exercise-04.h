/*
 * Exercise 7.4: Write a class named Person that represents the name and address
 * of a person. Use a string to hold each of these elements. Subsequent
 * exercises will incrementally add features to this class.
 */

#ifndef CHAPTER_07_EXERCISE_04_H_
#define CHAPTER_07_EXERCISE_04_H_

#include <string>  // std::string

struct Person {
  std::string name;
  std::string address;
};

#endif  // CHAPTER_07_EXERCISE_04_H_
