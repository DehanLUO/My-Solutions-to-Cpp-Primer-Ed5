/*
 * Exercise 3.6: Use a range for to change all the characters in a string to X.
 */

#include <iostream>  // std::getline, std::cout
#include <string>    // std::string

int main() {
  std::string str;
  std::cout << "Enter a string: ";
  std::getline(std::cin, str);  // Read the entire line including whitespace

  // Use range-based for loop to change each character to 'X'
  for (auto &ch : str) {
    ch = 'X';
  }

  std::cout << "Modified string: " << str << '\n';
  return 0;
}

/*
 * $ g++ -o main exercise03-06.cc && ./main
 * Enter a string:  The quick brown fox jumps over the lazy dog.
 * Modified string: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
 */