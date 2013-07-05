/*
 * Exercise 9.49: A letter has an ascender if, as with d or f, part of the
 * letter extends above the middle of the line. A letter has a descender if, as
 * with p or g, part of the letter extends below the line. Write a program that
 * reads a file containing words and reports the longest word that contains
 * neither ascenders nor descenders.
 */

#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <string>    // std::string

// Letters with ascenders (extend above the middle line)
const std::string ascenders = "bdfhkltABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Letters with descenders (extend below the line)
const std::string descenders = "gjpqy";

/**
 * @brief Checks if a word contains any ascenders or descenders
 * @param word The word to check
 * @return true if word contains no ascenders or descenders, false otherwise
 */
bool HasNoAscendersOrDescenders(const std::string& word) {
  return word.find_first_of(ascenders) == std::string::npos &&
         word.find_first_of(descenders) == std::string::npos;
}

/**
 * @brief Finds the longest word in a file with no ascenders or descenders
 * @param filename The name of the file to read
 * @return The longest qualifying word, or empty string if none found
 */
std::string FindLongestQualifyingWord(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error opening file: " << filename << "\n";
    return "";
  }

  std::string longest_word;
  std::string current_word;

  while (file >> current_word) {
    // Remove punctuation from the end of the word
    while (!current_word.empty() && ispunct(current_word.back())) {
      current_word.pop_back();
    }

    if (HasNoAscendersOrDescenders(current_word) &&
        current_word.length() > longest_word.length()) {
      longest_word = current_word;
    }
  }

  return longest_word;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  std::string result = FindLongestQualifyingWord(argv[1]);

  if (!result.empty()) {
    std::cout << "The longest word with no ascenders or descenders is: "
              << result << "\n";
  } else {
    std::cout << "No qualifying words found in the file.\n";
  }

  return EXIT_SUCCESS;
}

/*
 * $ g++ -o main chapter-09/exercise-49.cc && ./main data/book_sales
 * The longest word with no ascenders or descenders is: 0-201-82470-1
 */
