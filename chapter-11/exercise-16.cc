/*
 * Exercise 11.16: Using a map iterator write an expression that assigns a value
 * to an element
 */

#include <iostream>  // std::cout
#include <map>       // std::map
#include <string>    // std::string

int main() {
  std::map<std::string, int> word_counts = {{"apple", 5}, {"banana", 3}};

  // Get an iterator to an existing element
  auto it = word_counts.find("apple");

  // Check if element exists before assigning
  if (it != word_counts.end()) {
    // Assign a new value using the iterator
    it->second = 10;  // Changes apple's count from 5 to 10

    std::cout << "Updated count for 'apple': " << word_counts["apple"] << '\n';
  }

  // Another way: Using iterator from begin()
  auto first_it = word_counts.begin();
  first_it->second = 7;  // Changes the first element's value

  std::cout << "First element count is now: " << first_it->second << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-16.cc && ./main
 * Updated count for 'apple': 10
 * First element count is now: 7
 */
