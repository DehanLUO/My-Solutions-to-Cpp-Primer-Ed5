/*
 * Exercise 8.12: Why didn’t we use in-class initializers in PersonInfo?
 */

#ifndef CHAPTER_08_EXERCISE_12_H_
#define CHAPTER_08_EXERCISE_12_H_

#include <string>  // std::string
#include <vector>  // std::vector

/**
 * @brief PersonInfo struct without in-class initializers
 *
 * Rationale for omitting in-class initializers:
 * 1. Default initialization is sufficient:
 *    - std::string initializes to empty by default
 *    - std::vector initializes to empty by default
 *
 * 2. Avoids unnecessary default constructions:
 *    - Prevents redundant initialization when values will be immediately
 *      overwritten
 */

// members are public by default; see § 7.2 (p. 268)
struct PersonInfo {
  std::string name;
  std::vector<std::string> phones;
};

#endif  // CHAPTER_08_EXERCISE_12_H_
