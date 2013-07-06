/*
 * Exercise 11.38: Rewrite the word-counting (§ 11.1, p. 421) and
 * word-transformation (§ 11.3.6, p. 440) programs to use an unordered_map.
 */

#ifndef CHAPTER_11_EXERCISE_38_H_
#define CHAPTER_11_EXERCISE_38_H_

#include <cstddef>        // size_t
#include <fstream>        // std::ifstream
#include <iostream>       // std::cin, std::cout
#include <sstream>        // std::istringstream
#include <stdexcept>      // std::runtime_error
#include <string>         // std::string
#include <unordered_map>  // std::unordered_map

/**
 * @brief Counts word occurrences using unordered_map
 * @note Replaces original map-based implementation
 */
void WordCountingUnordered() {
  std::unordered_map<std::string, size_t> word_count;
  std::string word;

  /*
   * Performance advantage:
   * - Average O(1) insertion vs O(log n) for map
   * - Better cache locality
   */
  while (std::cin >> word) {
    ++word_count[word];
  }

  /*
   * Note about iteration order:
   * - No longer alphabetical
   * - Order depends on hash function
   * - Still valid for counting use case
   */
  for (const auto& word : word_count) {
    std::cout << word.first << " occurs " << word.second
              << (word.second > 1 ? " times" : " time") << '\n';
  }
}

/**
 * @brief Builds transformation map using unordered_map
 * @param map_file Input file stream with transformation rules
 * @return unordered_map of word transformations
 * @throws std::runtime_error On malformed rules
 */
std::unordered_map<std::string, std::string> BuildUnorderedMap(
    std::ifstream& map_file) {
  std::unordered_map<std::string, std::string> trans_map;
  std::string key;
  std::string value;

  /*
   * Implementation notes:
   * - Same interface as ordered version
   * - Faster O(1) average insertions
   * - No automatic sorting by key
   */
  while (map_file >> key && std::getline(map_file, value)) {
    if (value.size() > 1) {
      trans_map[key] = value.substr(1);
    } else {
      throw std::runtime_error("no rule for " + key);
    }
  }
  return trans_map;
}

/**
 * @brief Transforms words using unordered_map
 * @param word Input word to transform
 * @param trans_map Transformation rules map
 * @return Transformed word or original if no rule exists
 */
const std::string& TransformUnordered(
    const std::string& word,
    const std::unordered_map<std::string, std::string>& trans_map) {
  /*
   * Performance benefit:
   * - Average O(1) lookup vs O(log n)
   * - Same interface as map version
   */
  auto found = trans_map.find(word);
  return (found != trans_map.end()) ? found->second : word;
}

/**
 * @brief Processes text transformations using unordered_map
 * @param map_file Stream with transformation rules
 * @param input_file Stream with text to transform
 */
void WordTransformUnordered(std::ifstream& map_file,
                            std::ifstream& input_file) {
  const auto trans_map = BuildUnorderedMap(map_file);
  std::string text_line;

  /*
   * Behavior identical to ordered version except:
   * - Different map implementation internally
   * - No ordering of transformation rules
   */
  while (std::getline(input_file, text_line)) {
    std::istringstream line_stream(text_line);
    std::string word;
    bool is_first_word = true;

    while (line_stream >> word) {
      std::cout << (is_first_word ? "" : " ")
                << TransformUnordered(word, trans_map);
      is_first_word = false;
    }
    std::cout << '\n';
  }
}

#endif  // CHAPTER_11_EXERCISE_38_H_