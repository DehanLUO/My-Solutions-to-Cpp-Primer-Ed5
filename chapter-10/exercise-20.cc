/*
 * Exercise 10.20: The library defines an algorithm named count_if. Like
 * find_if, this function takes a pair of iterators denoting an input range and
 * a predicate that it applies to each element in the given range. count_if
 * returns a count of how often the predicate is true. Use count_if to rewrite
 * the portion of our program that counted how many words are greater than
 * length 6.
 */

#include <algorithm>  // std::count_if
#include <iostream>   // std::cout
#include <string>     // std::string
#include <vector>     // std::vector

/**
 * @brief Counts and prints words longer than specified length
 * @param words The vector of strings to process
 * @param sz Minimum length threshold
 */
void CountLongWords(const std::vector<std::string>& words,
                    std::vector<std::string>::size_type sz) {
  // Count words longer than sz using count_if
  auto count =
      std::count_if(words.begin(), words.end(),
                    [sz](const std::string& s) { return s.size() > sz; });

  std::cout << count << " word" << (count != 1 ? "s" : "") << " longer than "
            << sz << " characters\n";
}

int main() {
  std::vector<std::string> words = {"programming", "in",        "modern",
                                    "C++",         "is",        "powerful",
                                    "and",         "expressive"};

  // Test with different length thresholds
  CountLongWords(words, 5);  // Count words > 5 characters
  CountLongWords(words, 3);  // Count words > 3 characters
  CountLongWords(words, 6);  // Count words > 6 characters

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-20.cc && ./main
 * 4 words longer than 5 characters
 * 4 words longer than 3 characters
 * 3 words longer than 6 characters
 */
