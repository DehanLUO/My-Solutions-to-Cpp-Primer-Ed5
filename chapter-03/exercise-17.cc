/*
 * Exercise 3.17: Read a sequence of words from cin and store the values a
 * vector. After you’ve read all the words, process the vector and change each
 * word to uppercase. Print the transformed elements, eight words to a line.
 */

#include <cctype>    // std::toupper
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

  // Process and print vector contents
  for (auto& word : vec) {    // For each string in vector
    for (auto& ch : word) {   // For each character in string
      ch = std::toupper(ch);  // Convert character to uppercase
    }
    std::cout << word << ' ';  // Print converted string
  }
  std::cout << '\n';  // Newline after output

  return 0;
}

/*
 * $ g++ -o main exercise-17.cc && ./main
 * Enter a sequence of strings: The quick brown fox jumps over the lazy dog.
 * THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.
 */