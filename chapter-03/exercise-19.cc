/*
 * Exercise 3.19: List three ways to define a vector and give it ten elements,
 * each with the value 42. Indicate whether there is a preferred way to do so
 * and why.
 */

#include <vector>  // std::vector

int main() {
  // vector<T>(n, val) constructor
  std::vector<int> vec_a(10, 42);

  // Copy from a target vector
  std::vector<int> vec_b(vec_a);

  // vector<T>v{}; constructor
  std::vector<int> vec_c{42, 42, 42, 42, 42, 42, 42, 42, 42, 42};

  // Assign after default construction
  std::vector<int> vec_d;  // Empty vector
  vec_d.assign(10, 42);    // Overwrites with 10 copies of 42

  // Range constructor with fill iterator
  std::vector<int> vec_e(10);  // Vector with 10 default-initialized(0) elements
  std::fill_n(vec_e.begin(), 10, 42);  // Replace all elements with 42

  // Append
  std::vector<int> vec_f;  // Empty vector
  for (uint8_t idx = 0; idx < 10; ++idx) {
    vec_f.push_back(42);
  }

  return 0;
}

/*
 * `vector<T>v(n, val) is optimal for:
 * - Initializes directly without later modifications
 * - Clearly expresses intent "10 elements of 42"
 * - Avoids reallocations or redundant assignments
 */