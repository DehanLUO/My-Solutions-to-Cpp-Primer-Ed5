/*
 * Exercise 4.22: Extend the program that assigned high pass, pass, and fail
 * grades to also assign low pass for grades between 60 and 75 inclusive. Write
 * two versions: One version that uses only conditional operators; the other
 * should use one or more if statements. Which version do you think is easier to
 * understand and why?
 */

#include <iostream>  // std::cout

/**
 * @brief Determines grade using nested conditional operators
 * @param score The numeric grade (0-100)
 * @return const char* Grade description
 */
const char* GradeWithConditional(int score) {
  return (score > 90)    ? "high pass"
         : (score > 75)  ? "pass"
         : (score >= 60) ? "low pass"
                         : "fail";
}

/**
 * @brief Determines grade using if statements
 * @param score The numeric grade (0-100)
 * @return const char* Grade description
 */
const char* GradeWithIf(int score) {
  if (score > 90) return "high pass";
  if (score > 75) return "pass";
  if (score >= 60) return "low pass";
  return "fail";
}

int main() {
  // Test cases
  std::cout << "Conditional Operator Version:\n";
  std::cout << "95: " << GradeWithConditional(95) << '\n';
  std::cout << "85: " << GradeWithConditional(85) << '\n';
  std::cout << "70: " << GradeWithConditional(70) << '\n';
  std::cout << "50: " << GradeWithConditional(50) << '\n';

  // Test cases
  std::cout << "\nIf Statement Version:\n";
  std::cout << "95: " << GradeWithIf(95) << '\n';
  std::cout << "85: " << GradeWithIf(85) << '\n';
  std::cout << "70: " << GradeWithIf(70) << '\n';
  std::cout << "50: " << GradeWithIf(50) << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-22.cc && ./main
 * Conditional Operator Version:
 * 95: high pass
 * 85: pass
 * 70: low pass
 * 50: fail
 *
 * If Statement Version:
 * 95: high pass
 * 85: pass
 * 70: low pass
 * 50: fail
 */