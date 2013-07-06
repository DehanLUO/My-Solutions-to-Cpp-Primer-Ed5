/*
 * Exercise 11.20: Rewrite the word-counting program from § 11.1 (p. 421) to use
 * insert instead of subscripting. Which program do you think is easier to write
 * and read? Explain your reasoning.
 */

#include <cstddef>   // size_t
#include <iostream>  // std::cin, std::cout
#include <map>       // std::map, std::pair
#include <string>    // std::string
#include <utility>   // std::pair

/*
 * Subscripting advantages:
 * - More concise syntax
 * - Automatic handling of new elements
 * Insert advantages:
 * - Explicit control flow
 * - Better performance when avoiding default initialization
 * - Shows underlying map mechanics clearly
 */

int main() {
  std::map<std::string, size_t> word_count;
  std::string input_word;

  while (std::cin >> input_word) {
    /*
     * Attempt insertion of {word, 0} pair
     * insert returns pair<iterator, bool> where:
     * - iterator points to existing or new element
     * - bool indicates whether insertion occurred
     */
    std::pair<std::map<std::string, size_t>::iterator, bool> result =
        word_count.insert({input_word, 0});

    /*
     * Whether newly inserted or already existing,
     * increment the count through the returned iterator
     */
    ++(result.first->second);
  }

  /*
   * Range-for loop through all word-count pairs
   * Note use of reference to avoid copying
   */
  for (const auto& word_pair : word_count) {
    std::cout << word_pair.first << " occurs " << word_pair.second
              << ((word_pair.second > 1) ? " times" : " time") << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-20.cc && ./main
 * The quick brown fox jumps over the lazy dog.
 * The occurs 1 time
 * brown occurs 1 time
 * dog. occurs 1 time
 * fox occurs 1 time
 * jumps occurs 1 time
 * lazy occurs 1 time
 * over occurs 1 time
 * quick occurs 1 time
 * the occurs 1 time
 */
