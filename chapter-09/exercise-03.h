/*
 * Exercise 9.3: What are the constraints on the iterators that form iterator
 * ranges?
 */

#ifndef CHAPTER_09_EXERCISE_03_H_
#define CHAPTER_09_EXERCISE_03_H_

#include <vector>  // std::vector

/*
 * Constraints for valid iterator ranges [begin, end)
 * 1. Dereferenceability: begin must be dereferenceable or equal to end
 * 2. Reachability: end must be reachable from begin via ++
 * 3. Ordering: begin must precede end in the sequence
 * 4. Validity: Both iterators must refer to same container
 */

/**
 * @brief Demonstration of valid/invalid ranges
 */
void DemonstrateRanges() {
  std::vector<int> vec{1, 2, 3, 4, 5};

  // Valid range
  auto valid_begin = vec.begin();
  auto valid_end = vec.end();

  // Invalid cases:
  // 1. Unreachable end
  // auto invalid_end = vec.begin() + 10;

  // 2. Reversed order (would violate ordering constraint)
  // for (auto it = vec.end(); it != vec.begin(); --it)
  for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit) {
    ;  //
  }

  // 3. Different containers (would violate §27.2)
  std::vector<int> vec2;
  // auto mismatch_begin = vec.begin();
  // auto mismatch_end = vec2.end();
}

#endif  // CHAPTER_09_EXERCISE_03_H_
