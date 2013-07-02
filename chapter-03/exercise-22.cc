/*
 * Exercise 3.22: Revise the loop that printed the first paragraph in text to
 * instead change the elements in text that correspond to the first paragraph to
 * all uppercase. After you’ve updated text, print its contents.
 */

#include <cctype>    // std::toupper
#include <iostream>  // std::getline, std::cout, std::cerr
#include <string>    // std::string
#include <vector>    // std::vector

int main() {
  std::string paragraph;          // Stores each input line/paragraph
  std::vector<std::string> text;  // Stores all paragraphs

  std::cout << "Enter a sequence of paragraphs:\n";

  // Process first paragraph (convert to uppercase)
  {
    // Read first line from standard input
    if (!std::getline(std::cin, paragraph) || paragraph.empty()) {
      std::cerr << "No input!";  // Error if no input provided
      return -1;
    }

    // Convert all characters in first paragraph to uppercase
    for (auto it = paragraph.begin(); it != paragraph.end(); ++it) {
      *it = std::toupper(*it);  // Modify each character in place
    }

    text.emplace_back(paragraph);  // Store modified first paragraph
  }

  // Read remaining paragraphs (unchanged)
  while (std::getline(std::cin, paragraph)) {
    text.emplace_back(paragraph);  // Store subsequent paragraphs as-is
  }

  // Print all paragraphs
  for (auto it = text.cbegin(); it != text.cend(); ++it) {
    std::cout << *it << '\n';
  }

  return 0;  // Successful execution
}

/*
 * $ g++ -o main exercise-22.cc  && ./main
 * Enter a sequence of paragraphs:
 * The quick brown fox jumps over the lazy dog.
 * Pack my box with five dozen liquor jugs.
 * 1234567890
 * THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.
 * Pack my box with five dozen liquor jugs.
 * 1234567890
 */