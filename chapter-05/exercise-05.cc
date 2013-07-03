/*
 * Exercise 5.5: Using an if–else statement, write your own version of the
 * program to generate the letter grade from a numeric grade.
 */

#include <array>        // std::array
#include <iostream>     // std::cout
#include <string>       // std::string
#include <string_view>  // std::string_view

std::string GenerateLetterGrade(const int numeric_grade) {
  // Validate input
  if (numeric_grade < 0 || numeric_grade > 100) return "Invalid Grade";

  // Base letter grades
  const std::array<std::string_view, 6>  //
      base_grades = {"F", "D", "C", "B", "A", "A++"};

  // Determine base letter grade
  std::string letter_grade;
  if (numeric_grade < 60) {
    letter_grade += base_grades[0];
    return letter_grade;
  }

  letter_grade = base_grades[(numeric_grade - 50) / 10];

  if (100 == numeric_grade) return letter_grade;  // A++ case handled separately

  // Add modifiers
  if (numeric_grade % 10 > 7) {
    letter_grade += '+';  // grades ending in 8 or 9 get a +
  } else if (numeric_grade % 10 < 3) {
    letter_grade += '-';  // grades ending in 0, 1, or 2 get a -
  }

  return letter_grade;
}

int main() {
  // Test cases
  const std::array<int, 10> test_grades =  //
      {45, 62, 75, 81, 89, 93, 100, 77, 58, 102};

  for (int grade : test_grades) {
    std::cout << grade << " -> " << GenerateLetterGrade(grade) << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-05.cc && ./main
 * 45 -> F
 * 62 -> D-
 * 75 -> C
 * 81 -> B-
 * 89 -> B+
 * 93 -> A
 * 100 -> A++
 * 77 -> C
 * 58 -> F
 * 102 -> Invalid Grade
 */