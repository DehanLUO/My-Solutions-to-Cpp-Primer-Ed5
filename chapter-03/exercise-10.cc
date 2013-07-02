/*
 * Exercise 3.10: Write a program that reads a string of characters including
 * punctuation and writes what was read but with the punctuation removed.
 */

#include <cctype>    // std::ispunct
#include <iostream>  // std::getline, std::cout
#include <string>    // std::string

int main() {
  std::string input;

  std::cout << "Enter a string with punctuation:\n";
  std::getline(std::cin, input);  // Read entire line including spaces

  for (const char& ch : input) {
    if (!std::ispunct(ch)) {  // If character is NOT punctuation
      std::cout << ch;
    }
  }
  std::cout << '\n';

  return 0;
}

/*
 * Enter a string with punctuation:
 *  The quick brown fox jumps over the lazy dog.
 *  The quick brown fox jumps over the lazy dog
 */