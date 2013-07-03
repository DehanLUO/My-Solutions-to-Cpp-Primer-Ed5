/*
 * Exercise 5.17: Given two vectors of ints, write a program to determine
 * whether one vector is a prefix of the other. For vectors of unequal length,
 * compare the number of elements of the smaller vector. For example, given the
 * vectors containing 0, 1, 1, and 2 and 0, 1, 1, 2, 3, 5, 8, respectively your
 * program should return true.
 */

#include <ios>       // std::boolalpha
#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Checks if one vector is a prefix of another
 * @param first_vector The potential prefix vector
 * @param second_vector The vector to check against
 * @return true if first_vector is a prefix of second_vector
 *
 * The function handles vectors of unequal length by only comparing
 * elements up to the length of the shorter vector. An empty vector
 * is considered a prefix of any vector.
 */
bool IsVectorPrefix(const std::vector<int>& first_vector,
                    const std::vector<int>& second_vector) {
  /*
   * Algorithm selection rationale:
   * 1. Explicit iteration provides clearest intent demonstration
   * 2. Early termination when mismatch found
   * 3. Handles edge cases (empty vectors) naturally
   */
  const size_t prefix_length = first_vector.size();
  const size_t comparison_length = second_vector.size();

  // Handle empty vector cases
  if (prefix_length == 0) return true;
  if (comparison_length == 0) return false;
  if (prefix_length > comparison_length) return false;

  // Element-by-element comparison
  for (size_t i = 0; i < prefix_length; ++i) {
    if (first_vector[i] != second_vector[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  // Test cases demonstrating functionality
  const std::vector<int> empty_vector;
  const std::vector<int> short_vector{0, 1, 1};
  const std::vector<int> long_vector{0, 1, 1, 2, 3, 5, 8};
  const std::vector<int> mismatch_vector{0, 1, 2};

  // Demonstration of basic functionality
  std::cout << std::boolalpha  //
            << IsVectorPrefix(empty_vector, short_vector) << ' '
            << IsVectorPrefix(short_vector, long_vector) << ' '
            << IsVectorPrefix(mismatch_vector, long_vector);

  return 0;
}
/*
 * $ g++ -o main chapter-05/exercise-17.cc && ./main
 * true true false
 */
