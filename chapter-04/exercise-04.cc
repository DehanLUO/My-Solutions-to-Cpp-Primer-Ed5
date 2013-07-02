/*
 * Exercise 4.4: Parenthesize the following expression to show how it is
 * evaluated. Test your answer by compiling the expression (without parentheses)
 * and printing its result.
 *     12 / 3 * 4 + 5 * 15 + 24 % 4 / 2
 */

#include <iostream>  // std::cout

int main() {
  // Original expression with implicit grouping
  int result = 12 / 3 * 4 + 5 * 15 + 24 % 4 / 2;

  int explicit_result = ((12 / 3) * 4) + (5 * 15) + ((24 % 4) / 2);

  std::cout << "Original result: " << result << '\n'  //
            << "Explicitly group result: " << explicit_result << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-04.cc && ./main
 * Original result: 91
 * Explicitly group result: 91
 */