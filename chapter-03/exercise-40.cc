/*
 * Exercise 3.40: Write a program to define two character arrays initialized
 * from string literals. Now define a third character array to hold the
 * concatenation of the two arrays. Use strcpy and strcat to copy the two arrays
 * into the third.
 */

#include <cstring>   // strcpy, strcat
#include <iostream>  // std::cout

int main() {
  // Initialize two C-style strings from string literals
  const char str1[] = "Hello, ";
  const char str2[] = "World!";

  // Calculate total length need (+1 for null terminator)
  // -1 because both strings include their own null terminators
  constexpr size_t total_len = sizeof(str1) + sizeof(str2) - 1;

  // Create buffer for concatenated result
  char result[total_len] = {};  // Zero-initialized

  strcpy(result, str1);
  strcat(result, str2);

  std::cout << "Static array: " << result << '\n';

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-40.cc && ./main
 * Static array: Hello, World!
 */