/*
 * Exercise 4.12: Assuming i, j, and k are all ints, explain what i != j < k
 * means.
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates operator precedence in i != j < k expression
 * @return Evaluation steps as string
 */
std::string ExplainComparison(int i, int j, int k) {
  // Parenthesized to show actual evaluation order: i != (j < k)
  bool result = i != (j < k);

  std::string explanation = "Expression: i != j < k\n";
  explanation += "1. First evaluates j < k: " + std::to_string(j) + " < " +
                 std::to_string(k) + " → " + std::to_string(j < k) + "\n";
  explanation +=
      "2. Then compares i != (result from step 1): " + std::to_string(i) +
      " != " + std::to_string(j < k) + " → " + std::to_string(result) + "\n";
  return explanation;
}

int main() {
  // Test cases demonstrating the behavior
  int i = 1, j = 2, k = 3;  // Case 1: 1 != (2 < 3) → 1 != true → 1 != 1 → false
  std::cout << ExplainComparison(i, j, k);

  i = 2;
  j = 1;
  k = 0;  // Case 2: 2 != (1 < 0) → 2 != false → 2 != 0 → true
  std::cout << "\n" << ExplainComparison(i, j, k);

  return 0;
}
/*
 * $ g++ -o main chapter-04/exercise-12.cc && ./main
 * Expression: i != j < k
 * 1. First evaluates j < k: 2 < 3 → 1
 * 2. Then compares i != (result from step 1): 1 != 1 → 0
 *
 * Expression: i != j < k
 * 1. First evaluates j < k: 1 < 0 → 0
 * 2. Then compares i != (result from step 1): 2 != 0 → 1
 */