/*
 * Exercise 3.7: What would happen if you define the loop control variable in
 * the previous exercise as type char? Predict the results and then change your
 * program to use a char to see if you were right.
 */

#include <iostream>  // std::getline, std::cout
#include <string>    // std::string

int main() {
  std::string str;
  std::cout << "Enter a string: ";
  std::getline(std::cin, str);  // Read the entire line including whitespace

  // Use range-based for loop to change each character to 'X'
  for (char ch : str) {
    /*
     * The loop variable `ch` is declared as char. This means:
     * - `ch` is a copy of each character in `str`
     * - When you assign 'X' to `ch`, you only modify the copy
     * - The original characters in `str` remain unchanged
     */
    ch = 'X';
  }

  std::cout << "Modified string: " << str << '\n';
  return 0;
}

/*
 * $ g++ -o main exercise03-06.cc && ./main
 * Enter a string:  The quick brown fox jumps over the lazy dog.
 * Modified string:  The quick brown fox jumps over the lazy dog.
 */