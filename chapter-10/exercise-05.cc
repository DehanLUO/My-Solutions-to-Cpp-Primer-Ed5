/*
 * Exercise 10.5: In the call to equal on rosters, what would happen if both
 * rosters held C-style strings, rather than library strings?
 *     // roster2 should have at least as many elements as roster1
 *     equal(roster1.cbegin(), roster1.cend(), roster2.cbegin());
 */

#include <algorithm>  // std::equal
#include <cstring>    // strcmp
#include <iostream>   // std::cout
#include <iterator>   // std::begin, std::end
#include <string>     // std::string

/*
 * Demonstrates the critical difference between comparing C-style strings
 * and library strings with std::equal.
 */
void Demonstrate() {
  // C-style string arrays
  const char* roster1[] = {"apple", "banana", "cherry"};
  const char* roster2[] = {"apple", "banana", "cherry"};
  const char* roster3[] = {strdup("apple"), strdup("banana"), strdup("cherry")};
  const char* roster4[] = {"apple", "banana", "CHERRY"};

  /*
   * Dangerous Comparison:
   * std::equal compares pointer values, not string contents
   * This compares memory addresses rather than actual strings
   *
   * The std::begin() function returns an iterator for containers such as
   * std::vector or std::list. However, when applied to a built-in array, it
   * returns a raw pointer to the first element of the array. In the example
   * under discussion, the arrays roster1 and roster2 are arrays of C-sytle
   * string. When std::equal is invoked using these arrays, it compares the
   * elements using the equality operator by default. Since the elements are
   * `const char*`, this results in comparing pointer values---that is, memory
   * addresses---rather than the acutal string contents.
   */
  const bool bad_compare =
      std::equal(std::begin(roster1), std::end(roster1), std::begin(roster2));

  /*
   * In C++,string literals like "apple" are stored in a read-only section of
   * memory. If the same literal appears more than once, the compiler may reuse
   * the same memory location for efficiency. So even though roster1 and roster2
   * are separate arrays, their elements may point to the same addresses.
   * As a result, comparing the arrays with std::equal (which checks pointer
   * equality by default) might return true - not because the string contents
   * are equal, but because the pointers happen to be the same.
   * However, this behaviour is not guaranteed and should not be reliled on.
   */
  const bool bad_compare_2 =
      std::equal(std::begin(roster1), std::end(roster1), std::begin(roster3));

  /*
   * Correct Comparison:
   * Uses strcmp via custom comparator
   * Shows proper C-string comparison technique
   */
  const bool good_compare = std::equal(
      std::begin(roster1), std::end(roster1), std::begin(roster4),
      [](const char* a, const char* b) { return std::strcmp(a, b) == 0; });

  std::cout << "Pointer comparison (wrong): " << bad_compare << '\n'
            << "Pointer comparison (wrong_2): " << bad_compare_2 << '\n'
            << "String content comparison (correct): " << good_compare << '\n';

  /*
   * Critical Analysis:
   * The results might accidentally match if:
   * 1. Identical string literals are stored at same address (compiler
   *    optimization)
   * 2. Both arrays point to exactly the same memory locations
   *    But this is never reliable for actual string content comparison
   */
}

int main() {
  Demonstrate();

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-05.cc && ./main
 * Pointer comparison (wrong): 1
 * Pointer comparison (wrong_2): 0
 * String content comparison (correct): 0
 */
