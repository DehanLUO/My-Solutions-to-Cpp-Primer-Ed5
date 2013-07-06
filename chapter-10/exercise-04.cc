/*
 * Exercise 10.4: Assuming v is a vector<double>, what, if anything, is wrong
 * with calling accumulate(v.cbegin(), v.cend(), 0)?
 */

#include <iostream>  // std::cout
#include <numeric>   // std::accumulate
#include <vector>    // std::vector

/*
 * Demonstrates the integer accumulation pitfall with floating-point numbers.
 * Shows how initial value type affects the entire accumulation process.
 */
void DemonstrateAccumulateIssue() {
  const std::vector<double> floating_values = {1.2, 2.4, 3.6, 4.8};

  /*
   * Problematic Case:
   * Using integer 0 as initial value forces integer arithmetic,
   * causing truncation of decimal portions during accumulation
   */
  const int wrong_sum =
      std::accumulate(floating_values.cbegin(), floating_values.cend(), 0);

  /*
   * Corrected Case:
   * Using 0.0 maintains floating-point arithmetic throughout
   */
  const double correct_sum =
      std::accumulate(floating_values.cbegin(), floating_values.cend(), 0.0);

  std::cout << "Incorrect integer accumulation: " << wrong_sum << '\n'
            << "Proper floating-point accumulation: " << correct_sum << '\n';
}

int main() {
  /*
   * Type Conversion Analysis:
   * 1. The literal 0 has type int
   * 2. std::accumulate deduces its return type from the initial value
   * 3. Each addition performs integer arithmetic due to implicit conversion
   * 4. Decimal portions are discarded at each step
   */
  DemonstrateAccumulateIssue();

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-04.cc && ./main
 * Incorrect integer accumulation: 10
 * Proper floating-point accumulation: 12
 */
