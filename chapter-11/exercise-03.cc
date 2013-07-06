/*
 * Exercise 11.3: Write your own version of the word-counting program.
 */

#include <cctype>    // tolower, isalpha
#include <iostream>  // std::cin, std::cout
#include <map>       // std::map
#include <set>       // std::set
#include <string>    // std::string

/**
 * @brief Normalizes word by converting to lowercase and removing punctuation
 * @param word The word to normalize
 * @return Normalized version of the word
 */
std::string NormalizeWord(const std::string& word) {
  std::string result;
  for (char c : word) {
    if (isalpha(c)) {
      result += tolower(c);
    }
  }
  return result;
}

int main() {
  std::map<std::string, size_t> word_count;
  std::set<std::string> exclude = {
      "the", "but", "and", "or", "an", "a"  // all lowercase now
  };

  std::cout << "Enter text (Ctrl+D to end input):\n";
  std::string word;
  while (std::cin >> word) {
    // Normalize the word
    std::string normalized = NormalizeWord(word);

    // Skip empty words and excluded words
    if (!normalized.empty() && exclude.find(normalized) == exclude.end()) {
      ++word_count[normalized];
    }
  }

  // Print results sorted by word
  std::cout << "Word counts:\n";
  for (const auto& pair : word_count) {
    std::cout << pair.first << ": " << pair.second
              << (pair.second > 1 ? " occurrences" : " occurrence") << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-03.cc && ./main
 * Enter text (Ctrl+D to end input):
 * The quick brown fox jumps over the lazy dog.
 * Word counts:
 * brown: 1 occurrence
 * dog: 1 occurrence
 * fox: 1 occurrence
 * jumps: 1 occurrence
 * lazy: 1 occurrence
 * over: 1 occurrence
 * quick: 1 occurrence
 */
