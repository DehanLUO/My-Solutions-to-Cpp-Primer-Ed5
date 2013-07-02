/*
 * Exercise 4.23: The following expression fails to compile due to operator
 * precedence. Using Table 4.12 (p. 166), explain why it fails. How would you
 * fix it?
 *     string s = "word";
 *     string pl = s + s[s.size() - 1] == ’s’ ? "" : "s"
 * ;
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Demonstrates and fixes operator precedence issue
 */
void ExplainPrecedenceProblem() {
  std::string s = "word";

  // Original problematic expression:
  // string pl = s + s[s.size() - 1] == 's' ? "" : "s";
  // Issue: + has higher precedence than ==, so it evaluates as:
  // (s + s[s.size() - 1]) == 's' ? "" : "s"

  // Corrected version (parentheses):
  std::string pl = s + (s[s.size() - 1] == 's' ? "" : "s");

  std::cout << "Original intent: Add 's' unless word already ends with 's'\n";
  std::cout << "Corrected version 1 result: " << pl << "\n";
}

int main() {
  ExplainPrecedenceProblem();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-17.cc && ./main
 * Original intent: Add 's' unless word already ends with 's'
 * Corrected version 1 result: words
 */