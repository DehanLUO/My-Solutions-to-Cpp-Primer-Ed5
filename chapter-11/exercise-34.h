/*
 * Exercise 11.34: What would happen if we used the subscript operator instead
 * of find in the transform function?
 */

#ifndef CHAPTER_11_EXERCISE_34_H_
#define CHAPTER_11_EXERCISE_34_H_

#include <map>     // std::map
#include <string>  // std::string

/*
 * Critical difference between find() and operator[]:
 * - find() is const-correct and doesn't modify map
 * - operator[] will insert missing keys with default values
 * - operator[] cannot be used on const maps
 */

const std::string& Transform(const std::string& s,
                             const std::map<std::string, std::string>& m) {
  /*
   * Dangerous attempt using operator[]:
   * This would fail to compile because:
   * 1. m is const-qualified
   * 2. operator[] is non-const member function
   * 3. Even if not const, would insert default entry
   */
  // return m[s];

  // the actual map work; this part is the heart of the progrtam
  auto map_it = m.find(s);
  // if this word is in the transformation map
  if (map_it != m.cend()) {
    return map_it->second;  // use the replacement word
  }

  return s;  // otherwise return the original unchanged
}

#endif  // CHAPTER_11_EXERCISE_34_H_