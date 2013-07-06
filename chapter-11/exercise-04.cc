/*
 * Exercise 11.4: Extend your program to ignore case and punctuation. For
 * example, "example." "example," and "Example" should all increment the same
 * counter.
 */

#include <algorithm>  // std::remove_if
#include <cctype>     // ispunct, tolower
#include <iostream>   // std::cin, std::cout
#include <map>        // std::map
#include <set>        // std::set
#include <string>     // std::string

/**
 * @brief Normalizes word by converting to lowercase and removing punctuation
 * @param word The word to normalize
 * @return Normalized version of the word
 */
std::string NormalizeWord(std::string word) {
  // Convert to lowercase
  std::transform(word.begin(), word.end(), word.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  // Remove punctuation
  word.erase(std::remove_if(word.begin(), word.end(),
                            [](unsigned char c) { return std::ispunct(c); }),
             word.end());

  return word;
}

int main() {
  std::map<std::string, size_t> word_count;
  const std::set<std::string> exclude = {
      "the", "but", "and", "or", "an", "a"  // All lowercase
  };

  std::cout << "Enter text (Ctrl+D/Z to end input):\n";
  std::string word;
  while (std::cin >> word) {
    std::string normalized = NormalizeWord(word);

    if (!normalized.empty() && !exclude.count(normalized)) {
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
 * $ g++ -o main chapter-11/exercise-04.cc && ./main
 * Enter text (Ctrl+D/Z to end input):
 * The quick brown fox jumps over the lazy dog. DOG
 * Word counts:
 * brown: 1 occurrence
 * dog: 2 occurrences
 * fox: 1 occurrence
 * jumps: 1 occurrence
 * lazy: 1 occurrence
 * over: 1 occurrence
 * quick: 1 occurrence
 */
