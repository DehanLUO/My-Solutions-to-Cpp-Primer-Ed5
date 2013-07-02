/*
 * Exercise 3.15: Repeat the previous program but read strings this time.
 */

#include <iostream>  // std::cin, std::cout
#include <string>    // std::string
#include <vector>    // std::vector

int main() {
  std::vector<std::string> vec;  // vector to store the strings
  std::string str;               // variable to hold each input string

  std::cout << "Enter a sequence of strings: ";

  // Read strings until end-of-file or invalid input
  while (std::cin >> str) {
    vec.emplace_back(str);  // Add each string to the vector
  }

  // Print the vector contents to verify
  for (const auto item : vec) {
    std::cout << item << ' ';
  }
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise-15.cc  && ./main
 * Enter a sequence of strings: The quick brown fox jumps over the lazy dog.
 * The quick brown fox jumps over the lazy dog.
 */