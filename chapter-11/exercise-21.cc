/*
 * Exercise 11.21: Assuming word_count is a map from string to size_t and word
 * is a string, explain the following loop:
 *     while (cin >> word)
 *       ++word_count.insert({word, 0}).first->second;
 */

#include <iostream>  // std::cin
#include <map>       // std::map, std::pair
#include <string>    // std::string

int main() {
  std::map<std::string, size_t> word_count;
  std::string word;

  /*
   * The while loop condition reads words from standard input until
   * end-of-file or stream error. For each word processed:
   */
  while (std::cin >> word) {
    /*
     * The insert operation returns a pair containing:
     * - An iterator to the existing or newly inserted element
     * - A boolean indicating whether insertion occurred
     *
     * By immediately accessing ->second and applying ++, we ensure:
     * - New words get inserted with count 0 then incremented to 1
     * - Existing words have their count directly incremented
     */
    ++word_count.insert({word, 0}).first->second;
  }

  /*
   * Alternative equivalent implementation with clearer steps:
   * auto result = word_count.insert({word, 0});
   * ++(result.first->second);
   *
   * The original version is more compact but requires understanding
   * of operator precedence and map's return value structure.
   */

  return 0;
}
