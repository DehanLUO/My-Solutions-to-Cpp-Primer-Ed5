/*
 * Exercise 11.9: Define a map that associates words with a list of line numbers
 * on which the word might occur.
 */

#include <iostream>  // std::cout
#include <list>      // std::list
#include <map>       // std::map
#include <sstream>   // std::istringstream
#include <string>    // std::string

using WordLineMap = std::map<std::string, std::list<size_t>>;

/**
 * @brief Processes input text and builds word-to-line-numbers map
 * @param input The input text to process
 * @return Map of words to line numbers where they appear
 */
WordLineMap BuildWordLineMap(const std::string& input) {
  WordLineMap word_map;
  std::istringstream iss(input);
  std::string line;
  size_t line_number = 1;

  while (std::getline(iss, line)) {
    std::istringstream line_stream(line);
    std::string word;

    while (line_stream >> word) {
      // Remove punctuation and convert to lowercase
      word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);

      // Add line number to the word's list
      word_map[word].push_back(line_number);
    }
    line_number++;
  }

  return word_map;
}

/**
 * @brief Prints the word-to-line-numbers map
 * @param word_map The map to print
 */
void PrintWordLineMap(const WordLineMap& word_map) {
  for (const auto& word : word_map) {
    std::cout << word.first << ": ";
    for (auto line : word.second) {
      std::cout << line << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  std::string text =
      "Hello world!\n"
      "This is a test.\n"
      "Hello again, world.\n"
      "Test is important.";

  WordLineMap word_map = BuildWordLineMap(text);
  PrintWordLineMap(word_map);

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-09.cc && ./main
 * a: 2
 * again: 3
 * hello: 1 3
 * important: 4
 * is: 2 4
 * test: 2 4
 * this: 2
 * world: 1 3
 */
