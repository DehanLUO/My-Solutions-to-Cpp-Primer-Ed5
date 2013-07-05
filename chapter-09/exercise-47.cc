/*
 * Exercise 9.47: Write a program that finds each numeric character and then
 * each alphabetic character in the string "ab2c3d7R4E6". Write two versions of
 * the program. The first should use find_first_of, and the second
 * find_first_not_of.
 */

#include <iostream>
#include <string>

void FindWithFirstOf() {
  std::string s = "ab2c3d7R4E6";
  const std::string numbers = "0123456789";
  const std::string letters =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  std::cout << "Using find_first_of:\n";

  // Find all numeric characters
  std::cout << "Numeric characters at positions: ";
  size_t pos = 0;
  while ((pos = s.find_first_of(numbers, pos)) != std::string::npos) {
    std::cout << pos << " (" << s[pos] << ") ";
    ++pos;
  }
  std::cout << "\n";

  // Find all alphabetic characters
  std::cout << "Alphabetic characters at positions: ";
  pos = 0;
  while ((pos = s.find_first_of(letters, pos)) != std::string::npos) {
    std::cout << pos << " (" << s[pos] << ") ";
    ++pos;
  }
  std::cout << "\n\n";
}

void FindWithFirstNotOf() {
  std::string s = "ab2c3d7R4E6";
  const std::string numbers = "0123456789";
  const std::string letters =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  std::cout << "Using find_first_not_of:\n";

  // Find all numeric characters (by finding what's not letters)
  std::cout << "Numeric characters at positions: ";
  size_t pos = 0;
  while ((pos = s.find_first_not_of(letters, pos)) != std::string::npos) {
    std::cout << pos << " (" << s[pos] << ") ";
    ++pos;
  }
  std::cout << "\n";

  // Find all alphabetic characters (by finding what's not numbers)
  std::cout << "Alphabetic characters at positions: ";
  pos = 0;
  while ((pos = s.find_first_not_of(numbers, pos)) != std::string::npos) {
    // Verify it's actually a letter (not other punctuation)
    if (isalpha(s[pos])) {
      std::cout << pos << " (" << s[pos] << ") ";
    }
    ++pos;
  }
  std::cout << "\n";
}

int main() {
  FindWithFirstOf();
  FindWithFirstNotOf();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-47.cc && ./main
 * Using find_first_of:
 * Numeric characters at positions: 2 (2) 4 (3) 6 (7) 8 (4) 10 (6)
 * Alphabetic characters at positions: 0 (a) 1 (b) 3 (c) 5 (d) 7 (R) 9 (E)
 *
 * Using find_first_not_of:
 * Numeric characters at positions: 2 (2) 4 (3) 6 (7) 8 (4) 10 (6)
 * Alphabetic characters at positions: 0 (a) 1 (b) 3 (c) 5 (d) 7 (R) 9 (E)
 */
