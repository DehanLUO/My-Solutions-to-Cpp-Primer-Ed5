/*
 * Exercise 9.22: Assuming iv is a vector of ints, what is wrong with the
 * following program? How might you correct the problem(s)?
 *     vector<int>::iterator iter = iv.begin(),
 *                           mid = iv.begin() + iv.size() / 2;
 *     while (iter != mid)
 *       if (*iter == some_val)
 *         iv.insert(iter, 2 * some_val);
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector, insert()

/**
 * @brief Demonstrates and fixes the problematic vector insertion loop
 *
 * Original issues:
 * 1. Iterator invalidation during insertion
 * 2. Infinite loop potential
 * 3. Midpoint recalculation needed
 */
void FixedVectorInsertion(std::vector<int>& iv, int some_val) {
  /*
   * Problem 1: Storing mid upfront is dangerous because:
   * - insertions before mid will move it
   * - Need to recompute after each insertion
   */
  auto iter = iv.begin();

  /*
   * Problem 2: Must store original size first because:
   * - iv.size() changes with each insertion
   * - Prevents infinite loops
   */
  const auto original_size = iv.size();
  const auto original_mid = iv.begin() + original_size / 2;

  /*
   * Solution Approach:
   * 1. Track position rather than direct iterator comparison
   * 2. Use index-based loop
   * 3. Update insert position properly
   */
  for (size_t i = 0; i < original_size / 2;) {
    if (iv[i] == some_val) {
      /*
       * Correct insertion method:
       * 1. Get fresh iterator each time
       * 2. insert() returns new iterator
       * 3. Skip next element (the one we just inserted)
       */
      auto insert_pos = iv.begin() + i;
      insert_pos = iv.insert(insert_pos, 2 * some_val);
      i += 2;  // Skip original and inserted elements
    } else {
      ++i;
    }
  }
}

/**
 * @brief Safer alternative using modern C++ features
 */
void ModernFixedInsertion(std::vector<int>& iv, int some_val) {
  std::vector<int> temp;
  temp.reserve(iv.size() * 1.5);  // Prevent reallocations

  /* Process first half */
  for (auto iter = iv.begin(); iter != iv.begin() + iv.size() / 2; ++iter) {
    if (*iter == some_val) {
      temp.push_back(2 * some_val);
    }
    temp.push_back(*iter);
  }

  /* Copy second half unchanged */
  temp.insert(temp.end(), iv.begin() + iv.size() / 2, iv.end());

  iv.swap(temp);
}

int main() {
  std::vector<int> test_vec = {1, 2, 3, 2, 5, 2};
  const int target_val = 2;

  // Demonstrate fixes
  ModernFixedInsertion(test_vec, target_val);

  std::cout << "Corrected version output:\n";
  for (int num : test_vec) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-22.cc && ./main
 * Corrected version output:
 * 1 4 2 3 2 5 2
 */
