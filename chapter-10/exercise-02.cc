/*
 * Exercise 10.2: Repeat the previous program, but read values into a list of
 * strings.
 */

#include <algorithm>  // std::count
#include <cstdlib>    // EXIT_SUCCESS
#include <iostream>   // std::cin, std::cout
#include <list>       // std::list
#include <string>     // std::string, std::getline

/*
 * Counts occurrences of a target string in a list of strings.
 * Demonstrates generic algorithm usage with different container types.
 */
size_t CountStringOccurrences(const std::list<std::string>& strings,
                              const std::string& target) {
  /*
   * std::list requires traversal from beginning to end,
   * but provides better performance for insertions/deletions
   * compared to vector in middle positions
   */
  return std::count(strings.begin(), strings.end(), target);
}

/*
 * Reads whitespace-separated strings from standard input into a list.
 * Shows proper string input handling with getline.
 */
std::list<std::string> ReadStringListFromInput() {
  std::list<std::string> result;
  std::string current_string;

  /*
   * Using getline with whitespace delimiter demonstrates:
   * 1. Proper handling of strings containing spaces
   * 2. Clear termination on empty line
   */
  while (std::getline(std::cin >> std::ws, current_string, ' ')) {
    if (current_string.empty()) break;
    result.push_back(current_string);
  }

  return result;
}

int main() {
  std::cout << "Enter target string to count:\n";
  std::string target;
  std::getline(std::cin >> std::ws, target);

  std::cout << "Enter strings separated by spaces (empty line to stop):\n";
  const std::list<std::string> strings = ReadStringListFromInput();

  const size_t count = CountStringOccurrences(strings, target);
  std::cout << "The string \"" << target << "\" appears " << count
            << " times\n";

  return EXIT_SUCCESS;
}

/*
 * $ g++ -o main chapter-10/exercise-02.cc && ./main
 * Enter target string to count:
 * the
 * Enter strings separated by spaces (empty line to stop):
 * The quick brown fox jumps over the lazy dog.
 * The string "the" appears 1 times
 */
