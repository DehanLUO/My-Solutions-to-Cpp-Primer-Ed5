/*
 * Exercise 12.23: Write a program to concatenate two string literals, putting
 * the result in a dynamically allocated array of char. Write a program to
 * concatenate two library strings that have the same value as the literals used
 * in the first program.
 */

#include <cstring>   // strlen, strcpy
#include <iostream>  // std::cin, std::cout
#include <string>    // std::string

/**
 * @brief Concatenates two string literals into a dynamically allocated char
 * array
 * @param lit1 First string literal
 * @param lit2 Second string literal
 * @return Pointer to the concatenated result (caller must manage memory)
 */
inline char* ConcatenateLiterals(const char* lit1, const char* lit2) {
  // Calculate required size (+1 for null terminator)
  size_t len1 = strlen(lit1);
  size_t len2 = strlen(lit2);
  char* result = new char[len1 + len2 + 1];

  // Copy strings into new memory
  strcpy(result, lit1);
  strcpy(result + len1, lit2);

  return result;
}

/**
 * @brief Concatenates two std::string objects
 * @param str1 First string
 * @param str2 Second string
 * @return Concatenated string (memory managed by std::string)
 */
inline std::string ConcatenateStrings(const std::string& str1,
                                      const std::string& str2) {
  return str1 + str2;
}

int main() {
  // Part 1: Concatenate string literals
  const char* literal1 = "Hello, ";
  const char* literal2 = "world!";

  char* combined_literals = ConcatenateLiterals(literal1, literal2);
  std::cout << "Literal concatenation: " << combined_literals << "\n";

  // Clean up dynamically allocated memory
  delete[] combined_literals;

  // Part 2: Concatenate library strings
  std::string str1 = "Hello, ";
  std::string str2 = "world!";

  std::string combined_strings = ConcatenateStrings(str1, str2);
  std::cout << "String concatenation: " << combined_strings << "\n";

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-23.cc && ./main
 * Literal concatenation: Hello, world!
 * String concatenation: Hello, world!
 */
