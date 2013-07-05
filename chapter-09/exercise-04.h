/*
 * Exercise 9.4: Write a function that takes a pair of iterators to a
 * vector<int> and an int value. Look for that value in the range and return a
 * bool indicating whether it was found.
 */

#ifndef CHAPTER_09_EXERCISE_04_H_
#define CHAPTER_09_EXERCISE_04_H_

#include <vector>  // std::vector

/**
 * @brief Checks if value exists in iterator range [begin, end)
 * @tparam InputIt Input iterator type
 * @param begin Start of range
 * @param end One past the last element in range
 * @param value Value to search for
 * @return true if value found, false otherwise
 *
 * Requirements:
 * - InputIt must meet InputIterator requirements
 * - ValueType must be equality comparable with dereferenced iterator
 * - Range must be valid (end reachable from begin)
 */
template <typename InputIt, typename T>
bool ContainsValue(InputIt begin, InputIt end, const T value) {
  for (; begin != end; ++begin) {
    if (*begin == value) return true;
  }
  return false;
}

inline bool ContainsValue(std::vector<int>::iterator begin,
                          std::vector<int>::iterator end, int value) {
  return ContainsValue<std::vector<int>::iterator, int>(begin, end, value);
}

inline bool ContainsValue(std::vector<int>::const_iterator begin,
                          std::vector<int>::const_iterator end, int value) {
  return ContainsValue<std::vector<int>::const_iterator, int>(begin, end,
                                                              value);
}

#endif  // CHAPTER_09_EXERCISE_04_H_
