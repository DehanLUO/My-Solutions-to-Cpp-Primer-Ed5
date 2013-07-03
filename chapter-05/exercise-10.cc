/*
 * There is one problem with our vowel-counting program as we’ve implemented it:
 * It doesn’t count capital letters as vowels. Write a program that counts both
 * lower- and uppercase letters as the appropriate vowel—that is, your program
 * should count both ’a’ and ’A’ as part of aCnt, and so forth.
 */

#include <cctype>    // tolower()
#include <iostream>  // std::cin, std::cout

/**
 * Checks if character is a vowel (case-insensitive)
 * @param c - Character to check
 * @return True if vowel (a,e,i,o,u), false otherwise
 */
bool IsVowel(char character) {
  character = tolower(character);  // Normalize to lowercase
  return character == 'a' || character == 'e' || character == 'i' ||
         character == 'o' || character == 'u';
}

int main() {
  unsigned vowel_count = 0;  // Initialize counter
  char current;              // Stores current character

  std::cout << "Enter text (Ctrl+D to end): ";

  // Process input character by character
  while (std::cin.get(current)) {  // Read until EOF
    if (IsVowel(current)) {        // Check vowel using helper
      ++vowel_count;               // Increment if vowel found
    }
  }

  // Output results
  std::cout << "Total vowels: " << vowel_count << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-10.cc && ./main
 * Enter text (Ctrl+D to end): The quick brown fox jumps over the lazy dog.
 * Total vowels: 11
 */
