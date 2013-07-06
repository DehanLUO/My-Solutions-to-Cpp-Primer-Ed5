/*
 * Exercise 10.16: Write your own version of the biggies function using lambdas.
 */

#include <algorithm>  // std::sort, std::stable_sort, std::unique, std::for_each
#include <iostream>   // std::cout
#include <string>     // std::string
#include <vector>     // std::vector

/**
 * @brief Removes duplicates and sorts words alphabetically
 * @param words The vector of strings to process
 */
void EliminateDuplicates(std::vector<std::string>& words) {
  std::sort(words.begin(), words.end());
  auto end_unique = std::unique(words.begin(), words.end());
  words.erase(end_unique, words.end());
}

/**
 * @brief Prints words of given length or longer
 * @param words The vector of strings to process
 * @param sz Minimum length threshold for words to print
 *
 * Operation sequence:
 * 1. Remove duplicates and sort alphabetically
 * 2. Stable sort by length
 * 3. Find first word meeting length requirement
 * 4. Print qualifying words
 */
void Biggies(std::vector<std::string>& words,
             std::vector<std::string>::size_type sz) {
  // Step 1: Eliminate duplicates and sort alphabetically
  EliminateDuplicates(words);

  // Step 2: Stable sort by length, maintaining alphabetical order
  std::stable_sort(words.begin(), words.end(),
                   [](const std::string& a, const std::string& b) -> bool {
                     return a.size() < b.size();
                   });

  // Step 3: Find first word with size >= sz
  auto first_long_word = std::find_if(
      words.begin(), words.end(),
      [sz](const std::string& s) -> bool { return s.size() >= sz; });

  // Step 4: Count and print words meeting length requirement
  auto count = words.end() - first_long_word;
  std::cout << count << " words of length " << sz << " or longer:\n";

  std::for_each(first_long_word, words.end(),
                [](const std::string& s) { std::cout << s << ' '; });
  std::cout << '\n';
}

int main() {
  // Test case
  std::vector<std::string> words = {"the",  "quick", "brown", "fox", "jumps",
                                    "over", "the",   "lazy",  "dog"};

  // Test with different length thresholds
  Biggies(words, 3);
  Biggies(words, 4);
  Biggies(words, 5);

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-16.cc && ./main
 * 8 words of length 3 or longer:
 * dog fox the lazy over brown jumps quick
 * 5 words of length 4 or longer:
 * lazy over brown jumps quick
 * 3 words of length 5 or longer:
 * brown jumps quick
 */
