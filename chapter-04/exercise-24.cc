/*
 * Exercise 4.24: Our program that distinguished between high pass, pass, and
 * fail depended on the fact that the conditional operator is right associative.
 * Describe how that operator would be evaluated if the operator were left
 * associative.
 */

#include <iostream>  // std::cout

/**
 * @brief Shows the difference between right and left associative evaluation
 */
void ExplainAssociativity() {
  int score = 80;  // Test score

  // Current right-associative behavior (actual C++ behavior)
  const char* right_assoc = (score > 90)    ? "high pass"
                            : (score > 75)  ? "pass"
                            : (score >= 60) ? "low pass"
                                            : "fail";

  /*
   * Hypothetical left-associative behavior
   *   This would be parsed as: ((A ? B : C) ? D : E)
   *   const char* left_assoc_hypothetical =
   *     ((score > 90) ? "high pass" : (score > 75))
   *       ? "pass"
   *       : ((score >= 60) ? "low pass" : "fail");
   *
   * Hypothetical left-associative evaluation would:
   * 1. First evaluate (score > 90) ? "high pass" : (score > 75)
   *    (This yields boolean true/false instead of string)
   * 2. Then use that boolean to choose between "pass" or the next conditional
   * 3. Result would be incorrect type mixing and logical errors
   */
}

int main() {
  ExplainAssociativity();

  return 0;
}
