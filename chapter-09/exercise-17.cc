/*
 * Exercise 9.17: Assuming c1 and c2 are containers, what (if any) constraints
 * does the following usage place on the types of c1 and c2?
 *     if (c1 < c2)
 */

#include <list>    // std::list
#include <vector>  // std::vector

/*
 * The relational operator < between containers requires:
 * 1. Both containers must be of the same type (e.g., vector vs vector)
 *    - Comparing vector<int> with list<int> would fail
 * 2. The containers must be of the same template instance
 *    - vector<int> can compare with vector<int> but not vector<double>
 * 3. The element type must support the < operator
 *    - Elements must be comparable using operator<
 */

/**
 * @brief Demonstrates constraints for container comparison with operator<
 *
 * Shows valid and invalid comparison scenarios with explanations
 */
void DemonstrateContainerComparison() {
  std::vector<int> vec1{1, 2, 3};
  std::vector<int> vec2{4, 5, 6};
  std::list<int> list1{1, 2, 3};
  std::vector<double> vec_double{1.0, 2.0};

  // Valid comparison - same container type and comparable elements
  bool valid_comparison = (vec1 < vec2);  // true

  /*
   * Invalid comparisons below would cause compilation errors
   * Uncomment to see the errors
   */
  // bool invalid1 = (vec1 < list1);  // Error: different container types
  // bool invalid2 = (vec1 < vec_double);  // Error: different element types

  /*
   * Additional requirements:
   * - Both containers must use the same allocator type
   * - Comparison is lexicographical (element-by-element)
   * - First mismatching element defines the result
   */
}

/**
 * @brief Custom type demonstrating element comparability requirement
 */
struct NonComparable {
  int value;
  // No operator< defined
};

void DemonstrateElementRequirements() {
  std::vector<NonComparable> nc_vec1(3);
  std::vector<NonComparable> nc_vec2(3);

  // This would fail to compile - elements lack operator<
  // bool invalid_comparison = (nc_vec1 < nc_vec2);
}

int main() {
  DemonstrateContainerComparison();
  DemonstrateElementRequirements();

  return 0;
}
