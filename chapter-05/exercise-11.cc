/*
 * Exercise 5.11: Modify our vowel-counting program so that it also counts the
 * number of blank spaces, tabs, and newlines read.
 */

#include <cctype>    // tolower(), isspace()
#include <iostream>  // std::cin, std::cout

/**
 * Checks if character is a vowel (case-insensitive)
 * @param c - Character to check
 * @return True if vowel (a,e,i,o,u), false otherwise
 */
bool IsVowel(char c) {
  c = tolower(c);
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

/**
 * Checks if character is whitespace (space, tab, newline)
 * @param c - Character to check
 * @return True if whitespace, false otherwise
 */
bool IsSpecialWhitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

int main() {
  unsigned vowel_count = 0;       // Tracks vowel occurrences
  unsigned whitespace_count = 0;  // Tracks spaces/tabs/newlines
  char current;                   // Stores current character

  std::cout << "Enter text (Ctrl+D to end): ";

  while (std::cin.get(current)) {  // Read until EOF
    if (IsVowel(current)) {        // Vowel check
      ++vowel_count;
    }
    if (IsSpecialWhitespace(current)) {  // Whitespace check
      ++whitespace_count;
    }
  }

  // Output formatted results
  std::cout << "Analysis Results:\n"
            << "Vowels: " << vowel_count << '\n'
            << "Whitespace (spaces/tabs/newlines): " << whitespace_count
            << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-11.cc && ./main
 * Enter text (Ctrl+D to end): The quick brown fox jumps over the lazy dog.
 * Analysis Results:
 * Vowels: 11
 * Whitespace (spaces/tabs/newlines): 9
 */
