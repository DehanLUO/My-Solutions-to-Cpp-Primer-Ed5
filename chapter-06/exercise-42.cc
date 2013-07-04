/*
 * Exercise 6.42: Give the second parameter of make_plural (§ 6.3.2, p. 224) a
 * default argument of ’s’. Test your program by printing singular and plural
 * versions of the words success and failure.
 *     // return the plural version of word if ctr is greater than 1
 *     string make_plural(size_t ctr, const string &word, const string &ending)
 *     {
 *       return (ctr > 1) ? word + ending : word;
 *     }
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Returns the plural version of a word when count > 1
 * @param count The quantity determining pluralization
 * @param word The base word to pluralize
 * @param ending The plural ending (default 's')
 * @return Pluralized string when count > 1, otherwise original word
 *
 * Demonstrates proper use of default arguments with string parameters.
 * The default ending follows common English pluralization rules.
 */
std::string MakePlural(size_t count, const std::string& word,
                       const std::string& ending = "s") {
  /*
   * Implementation notes:
   * - Uses ternary operator for concise conditional logic
   * - Returns new string by value (safe for temporary usage)
   * - Default argument allows simple common case usage
   */
  return (count > 1) ? word + ending : word;
}

int main() {
  std::cout << "Singular: " << MakePlural(1, "apple") << "\n";
  std::cout << "Plural: " << MakePlural(2, "failure", "s") << "\n";
  std::cout << "Plural: " << MakePlural(2, "boss", "es") << "\n";

  return 0;
}

/* $ g++ -o main chapter-06/exercise-42.cc && ./main
 * Singular: apple
 * Plural: failures
 * Plural: bosses
 */
