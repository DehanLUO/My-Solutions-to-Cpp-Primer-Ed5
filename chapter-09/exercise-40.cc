/*
 * Exercise 9.40: If the program in the previous exercise reads 256 words, what
 * is its likely capacity after it is resized? What if it reads 512? 1,000?
 * 1,048?
 */

/*
 * This program explores the growth behaviour of std::vector when pre-allocated
 * with reserve() and subsequently resized beyond its initial capacity.
 *
 * The call to reserve(1024) ensures that the vector can store at least 1024
 * elements without triggering a reallocation. This is intended to improve
 * efficiency during repeated calls to push_back().
 *
 * Later, the call to resize(N + N/2) increases the size of the vector by 50%.
 * If this new size exceeds the current capacity, the vector will reallocate
 * memory, following a growth policy that is implementation-dependent—typically
 * doubling the previous capacity.
 *
 * The following scenarios demonstrate the vector’s likely capacity after
 * resizing, based on different numbers of words read from input:
 *
 * Case 1: 256 words
 * - After insertion, size() = 256, capacity() = 1024
 * - resize(256 + 128) = 384 < 1024
 * - → No reallocation occurs; capacity remains 1024
 *
 * Case 2: 512 words
 * - After insertion, size() = 512, capacity() = 1024
 * - resize(512 + 256) = 768 < 1024
 * - → No reallocation occurs; capacity remains 1024
 *
 * Case 3: 1000 words
 * - After insertion, size() = 1000, capacity() = 1024
 * - resize(1000 + 500) = 1500 > 1024
 * - → Reallocation occurs; capacity likely increases to 2048
 *
 * Case 4: 1048 words
 * - After insertion, size() = 1048
 * - Initial capacity of 1024 is already exceeded during insertion, so
 *   reallocation occurs during push_back()
 * - Assuming capacity doubles at this point, capacity becomes 2048
 * - resize(1048 + 524) = 1572 < 2048
 * - → No additional reallocation occurs; capacity remains 2048
 *
 * Conclusion:
 * For vectors that grow beyond their reserved capacity, the standard library
 * often reallocates with a geometric growth strategy (e.g., doubling). When the
 * resized size remains within the post-reallocation capacity, no further memory
 * allocation is triggered.
 */

#include <iostream>  // std::cin
#include <vector>    // std::vector

int main() {
  // A vector of string objects named svec is created. Initially, it is empty
  // and has minimal capacity (0)
  std::vector<std::string> svec;

  // This call pre-allocates memory for at least 1024 elements. It does not
  // change the size() of the vector. The purpose is to improve performance by
  // avoiding frequent reallocations during push_back
  svec.reserve(1024);

  // Words are read from cin, one at a time, until input ends. Each word is
  // appended to svec using push_back. If the number of words exceeds 1024, svec
  // will automatically reallocate additional storage beyond the reserved
  // capacity.
  std::string word;
  while (std::cin >> word) svec.push_back(word);

  // This increases the size of the vector by 50%.
  svec.resize(svec.size() + (svec.size() / 2));

  return 0;
}
