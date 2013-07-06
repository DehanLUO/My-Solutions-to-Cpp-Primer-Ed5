/*
 * Exercise 10.18: Rewrite biggies to use partition instead of find_if. We
 * described the partition algorithm in exercise 10.13 in § 10.3.1 (p. 387).
 */

#include <algorithm>  // std::sort, std::stable_sort, std::unique, std::for_each, std::partition
#include <iostream>  // std::cout
#include <string>    // std::string
#include <vector>    // std::vector

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
  auto first_long_word = std::partition(
      words.begin(), words.end(),
      [sz](const std::string& s) -> bool { return s.size() >= sz; });

  // Step 4: Count and print words meeting length requirement
  auto count = first_long_word - words.begin();
  std::cout << count << " words of length " << sz << " or longer:\n";

  std::for_each(words.begin(), first_long_word,
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
 * $ g++ -o main chapter-10/exercise-18.cc && ./main
 * 8 words of length 3 or longer:
 * dog fox the lazy over brown jumps quick
 * 5 words of length 4 or longer:
 * quick jumps brown lazy over
 * 3 words of length 5 or longer:
 * quick jumps brown
 */
