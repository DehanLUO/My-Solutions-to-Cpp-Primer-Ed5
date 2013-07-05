/*
 * Exercise 9.33: In the final example in this section what would happen if we
 * did not assign the result of insert to begin? Write a program that omits this
 * assignment to see if your expectation was correct.
 *     // safer: recalculate end on each trip
 *     // whenever the loop adds/erase elements
 *     while (begin != v.end()) {
 *       // do some processing
 *       ++begin; // advance begin because we want to insert after this elemet
 *       begin = v.insert(begin, 42); // insert the new value
 *       ++begin; // advance begin post the element we just added
 *     }
 */

#include <iostream>  // std::cout
#include <vector>    // std::vectpr

/**
 * @brief Correct version that assigns insert result
 */
void CorrectVersion() {
  std::vector<int> vint = {1, 2, 3};

  std::cout << "Correct version:\n";
  auto begin1 = vint.begin();
  while (begin1 != vint.end()) {
    ++begin1;
    begin1 = vint.insert(begin1, 42);  // Critical assignment
    ++begin1;
  }
  for (int num : vint) std::cout << num << ' ';
  std::cout << '\n';
}

/**
 * @brief Broken version that doesn't assign insert result
 */
void BrokenVersion() {
  std::vector<int> vint = {1, 2, 3};

  std::cout << "Broken version:\n";
  auto begin = vint.begin();
  while (begin != vint.end()) {
    ++begin;
    /*
     * Undefined behaviour occurs because:
     * - insert invalidates begin (since vectors may reallocate)
     * - we continue using the invalidated iterator
     */
    vint.insert(begin, 42);  // Missing assignment!
    ++begin;
  }
  // This will likely crash or produce garbage
  for (int num : vint) std::cout << num << ' ';
  std::cout << '\n';
}

int main() {
  CorrectVersion();
  // BrokenVersion();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-33.cc && ./main
 * Correct version:
 * 1 42 2 42 3 42
 */
