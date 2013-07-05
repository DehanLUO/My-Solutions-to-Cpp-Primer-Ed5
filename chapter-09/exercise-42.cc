/*
 * Exercise 9.42: Given that you want to read a character at a time into a
 * string, and you know that you need to read at least 100 characters, how might
 * you improve the performance of your program?
 */

#include <iostream>
#include <string>

void ReadCharactersOptimized() {
  std::string str;

  // Critical optimization: reserve space upfront
  str.reserve(100);  // Allocate memory for at least 100 characters

  char c;
  while (std::cin.get(c)) {  // Read character by character
    str.push_back(c);

    // Optional: break if you have some specific condition
    // if (str.size() >= 100) break;
  }

  std::cout << "Read " << str.size() << " characters: " << str << "\n";
}

int main() {
  std::cout << "Enter at least 100 characters (Ctrl+D to end):\n";
  ReadCharactersOptimized();
  return 0;
}
