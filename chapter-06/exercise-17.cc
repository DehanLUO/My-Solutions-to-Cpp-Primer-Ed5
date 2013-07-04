/*
 * Exercise 6.17: Write a function to determine whether a string contains any
 * capital letters. Write a function to change a string to all lowercase. Do the
 * parameters you used in these functions have the same type? If so, why? If
 * not, why not?
 */

#include <cctype>    // toupper, tolower
#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Checks if a string contains any capital letters
 * @param s The string to check (const reference)
 * @return bool True if any capitals found, false otherwise
 *
 * Uses const reference because:
 * 1. Doesn't need to modify the string
 * 2. Avoids copying large strings
 * 3. Can accept const strings and literals
 */
bool HasCapitalLetters(const std::string& s) {
  for (char c : s) {
    if (isupper(c)) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Converts a string to all lowercase
 * @param s The string to modify (non-const reference)
 *
 * Uses non-const reference because:
 * 1. Needs to modify the original string
 * 2. Changes should be visible to caller
 * 3. More efficient than returning a copy
 */
void ConvertToLowercase(std::string& s) {
  for (char& c : s) {
    c = tolower(c);
  }
}

/*
 * Parameter Type Analysis:
 *
 * Why different parameter types?
 * 1. HasCapitalLetters:
 *    - const reference because it only examines the string
 *    - Preserves original string
 *    - More flexible (accepts const strings/literals)
 *
 * 2. ConvertToLowercase:
 *    - Non-const reference because it modifies the string
 *    - Changes should affect caller's string
 *    - Can't accept const strings (by design)
 */

int main() {
  // Test HasCapitalLetters
  std::string test1 = "Hello World";
  std::cout << std::boolalpha;
  std::cout << "Has capitals? " << HasCapitalLetters(test1) << '\n';  // true
  std::cout << "Has capitals? " << HasCapitalLetters("lowercase")
            << '\n';  // false

  // Test ConvertToLowercase
  std::string test2 = "MAKE ME LOWERCASE";
  ConvertToLowercase(test2);
  std::cout << "Lowercased: " << test2 << '\n';  // "make me lowercase"

  return 0;
}

/* $ g++ -o main chapter-06/exercise-17.cc && ./main
 * Has capitals? true
 * Has capitals? false
 * Lowercased: make me lowercase
 */
