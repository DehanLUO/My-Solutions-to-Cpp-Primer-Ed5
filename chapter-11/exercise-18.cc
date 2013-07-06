/*
 * Exercise 11.18: Write the type of map_it from the loop on page 430 without
 * using auto or decltype.
 */

#include <cstddef>   // size_t
#include <iostream>  // std::cout
#include <map>       // std::map
#include <string>    // std::string

int main() {
  std::map<std::string, size_t> word_count;

  // get an iterator positioned on the first element
  // The explicit type of map_it is:
  std::map<std::string, size_t>::const_iterator map_it = word_count.cbegin();

  // compute the current iterator to the off-the-end iterator
  while (map_it != word_count.cend()) {
    // dereference the iterator to print the element by key-value pairs
    std::cout << map_it->first << " occurs " << map_it->second << " times "
              << '\n';
    ++map_it;  // increment the iterator to denote the next element
  }

  return 0;
}
