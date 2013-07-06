/*
 * Exercise 10.25: In the exercises for § 10.3.2 (p. 392) you wrote a version of
 * biggies that uses partition. Rewrite that function to use check_size and
 * bind.
 */

#include <algorithm>  // std::sort, std::stable_sort, std::unique, std::for_each, std::stable_partition
#include <functional>  // std::bind
#include <iostream>    // std::cout
#include <string>      // std::string
#include <vector>      // std::vector

/**
 * @brief Checks if string length is >= given size
 * @param s The string to check
 * @param sz The size threshold
 * @return True if s.size() >= sz
 */
bool CheckSize(const std::string& s, std::string::size_type sz) {
  return s.size() >= sz;
}

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
 * @brief Prints words of given length or longer using std::bind
 * @param words The vector of strings to process
 * @param sz Minimum length threshold for words to print
 */
void Biggies(std::vector<std::string>& words,
             std::vector<std::string>::size_type sz) {
  // Step 1: Eliminate duplicates and sort alphabetically
  EliminateDuplicates(words);

  // Step 2: Stable sort by length, maintaining alphabetical order
  std::stable_sort(words.begin(), words.end(),
                   [](const std::string& a, const std::string& b) {
                     return a.size() < b.size();
                   });

  // Step 3: Partition words by length using bind
  auto first_short_word =
      std::stable_partition(words.begin(), words.end(),
                            std::bind(CheckSize, std::placeholders::_1, sz));

  // Step 4: Count and print words meeting length requirement
  auto count = std::distance(words.begin(), first_short_word);
  std::cout << count << " word" << (count != 1 ? "s" : "") << " of length "
            << sz << " or longer:\n";

  std::for_each(words.begin(), first_short_word,
                [](const std::string& s) { std::cout << s << ' '; });
  std::cout << "\n\n";
}

int main() {
  std::vector<std::string> words = {"the",  "quick", "brown", "fox", "jumps",
                                    "over", "the",   "lazy",  "dog"};

  // Test with different length thresholds
  Biggies(words, 3);
  Biggies(words, 4);
  Biggies(words, 5);

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-25.cc && ./main
 * 8 words of length 3 or longer:
 * dog fox the lazy over brown jumps quick
 *
 * 5 words of length 4 or longer:
 * lazy over brown jumps quick
 *
 * 3 words of length 5 or longer:
 * brown jumps quick
 *
 */
