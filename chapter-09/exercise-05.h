/*
 * Exercise 9.5: Rewrite the previous program to return an iterator to the
 * requested element. Note that the program must handle the case where the
 * element is not found.
 */

#ifndef CHAPTER_09_EXERCISE_05_H_
#define CHAPTER_09_EXERCISE_05_H_

#include <vector>  // std::vector

/**
 * @brief Finds value in iterator range [begin, end)
 * @tparam InputIt Input iterator type
 * @tparam T Value type
 * @param begin Start of range
 * @param end One past the last element in range
 * @param value Value to search for
 * @return Iterator to found element, or end if not found
 *
 * Requirements:
 * - InputIt must meet InputIterator requirements
 * - ValueType must be equality comparable with dereferenced iterator
 * - Range must be valid (end reachable from begin)
 */
template <typename InputIt, typename T>
InputIt ContainsValue(InputIt begin, InputIt end, const T value) {
  for (; begin != end; ++begin) {
    if (*begin == value) break;
  }
  return begin;
}

inline std::vector<int>::iterator ContainsValue(
    std::vector<int>::iterator begin, std::vector<int>::iterator end,
    int value) {
  return ContainsValue<std::vector<int>::iterator, int>(begin, end, value);
}

inline std::vector<int>::const_iterator ContainsValue(
    std::vector<int>::const_iterator begin,
    std::vector<int>::const_iterator end, int value) {
  return ContainsValue<std::vector<int>::const_iterator, int>(begin, end,
                                                              value);
}

#endif  // CHAPTER_09_EXERCISE_05_H_
