/*
 * Exercise 11.8: Write a program that stores the excluded words in a vector
 * instead of in a set. What are the advantages to using a set?
 */

/*
 * Advantages of using set:
 * 1. Faster lookup: O(log n) vs O(n) for vector
 * 2. Automatic sorting: Elements always ordered
 * 3. Enforced uniqueness: No duplicate entries
 * 4. More semantic: Clearly expresses 'collection of unique items'
 */

#include <algorithm>  // find
#include <cctype>     // tolower
#include <iostream>   // std::cin, std::cout
#include <map>        // std::map
#include <set>        // std::set
#include <string>     // std::string
#include <vector>     // std::vector

// Version using vector for excluded words
void WordCountWithVector() {
  std::vector<std::string> exclude = {"the", "but", "and", "or", "an", "a"};
  std::map<std::string, size_t> word_count;
  std::string word;

  std::cout << "Using vector for excluded words:\n";
  while (std::cin >> word) {
    // Convert to lowercase
    std::transform(word.begin(), word.end(), word.begin(), tolower);

    // Check if word is in exclude vector (O(n) search)
    if (find(exclude.begin(), exclude.end(), word) == exclude.end()) {
      ++word_count[word];
    }
  }
}

// Version using set for excluded words
void WordCountWithSet() {
  std::set<std::string> exclude = {"the", "but", "and", "or", "an", "a"};
  std::map<std::string, size_t> word_count;
  std::string word;

  std::cout << "Using set for excluded words:\n";
  while (std::cin >> word) {
    std::transform(word.begin(), word.end(), word.begin(), tolower);

    // Check if word is in exclude set (O(log n) search)
    if (exclude.find(word) == exclude.end()) {
      ++word_count[word];
    }
  }
}

int main() {
  WordCountWithVector();

  WordCountWithSet();

  return 0;
}
