/*
 * Exercise 4.31: The program in this section used the prefix increment and
 * decrement operators. Explain why we used prefix and not postfix. What changes
 * would have to be made to use the postfix versions? Rewrite the program using
 * postfix operators.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Outputs vector elements to standard output
 * @param vec The vector<int> to display
 */
void Dump(const std::vector<int>& vec) {
  for (const auto& num : vec) {
    std::cout << num << ' ';
  }
}

/**
 * @brief Demonstrates prefix increment/decrement usage
 * @details Uses ++ix and --cnt operators which:
 * 1. Modify then return the value (no copies)
 * 2. Are more efficient for non-primitive types
 */
void PrefixVersion() {
  // Original prefix version (recommended)
  std::cout << "Prefix version:\n";

  std::vector<int> ivec(10);
  std::vector<int>::size_type cnt = ivec.size();

  /*
   * Prefix (++ix) increments and returns the new value
   * iterator& operator++() {
   *   // increment logic
   *   return *this;
   * }
   */
  for (std::vector<int>::size_type ix = 0; ix != ivec.size(); ++ix, --cnt) {
    ivec[ix] = cnt;  // Assign descending values
  }
  Dump(ivec);
  std::cout << "\n";
}

/**
 * @brief Demonstrates postfix increment/decrement usage
 * @details Uses ix++ and cnt-- operators which:
 * 1. Return copy of original value
 * 2. Then modify operand
 * 3. Create unnecessary temporaries with non-primitives
 */
void PostfixVersion() {
  // Postfix version (less efficient)
  std::cout << "Postfix version:\n";

  std::vector<int> ivec(10);
  std::vector<int>::size_type cnt = ivec.size();

  /*
   * Postfix (ix++) must create a copy of the old value before incrementing.
   * For complex objects, this copy operation can be expensive.
   * iterator operator++(int) {
   *   iterator temp = *this;
   *   ++*this;
   *   return temp;
   * }
   */
  for (std::vector<int>::size_type ix = 0; ix != ivec.size(); ix++, cnt--) {
    ivec[ix] = cnt;  // Assign descending values
  }
  Dump(ivec);
  std::cout << "\n";
}

int main() {
  PrefixVersion();   // Execute prefix demonstration
  PostfixVersion();  // Execute postfix demonstration

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-31.cc && ./main
 * Prefix version:
 * 10 9 8 7 6 5 4 3 2 1
 * Postfix version:
 * 10 9 8 7 6 5 4 3 2 1
 */