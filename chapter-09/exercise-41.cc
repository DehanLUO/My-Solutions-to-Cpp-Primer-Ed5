/*
 * Exercise 9.41: Write a program that initializes a string from a vector<char>.
 */

#include <iostream>  // std::cout
#include <string>    // std::string
#include <vector>    // std::vector

int main() {
  // Create and populate a vector<char>
  std::vector<char> char_vec = {'H', 'e', 'l', 'l', 'o', ' ',
                                'W', 'o', 'r', 'l', 'd', '!'};

  // Method 1: Using range constructor
  std::string str1(char_vec.begin(), char_vec.end());
  std::cout << "Method 1: " << str1 << '\n';

  // Method 2: Using string append
  std::string str2;
  str2.append(char_vec.begin(), char_vec.end());
  std::cout << "Method 2: " << str2 << '\n';

  // Method 3: Using string assign
  std::string str3;
  str3.assign(char_vec.begin(), char_vec.end());
  std::cout << "Method 3: " << str3 << '\n';

  // Method 4: Using string insert
  std::string str4;
  str4.insert(str4.begin(), char_vec.begin(), char_vec.end());
  std::cout << "Method 4: " << str4 << '\n';

  return 0;
}
