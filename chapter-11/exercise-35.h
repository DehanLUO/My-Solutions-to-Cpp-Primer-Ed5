/*
 * Exercise 11.35: In buildMap, what effect, if any, would there be from
 * rewriting
 *     trans_map[key] = value.substr(1);
 * as trans_map.insert({key, value.substr(1)})?
 */

#ifndef CHAPTER_11_EXERCISE_35_H_
#define CHAPTER_11_EXERCISE_35_H_

#include <fstream>    // std::ifstream, std::ofstream
#include <map>        // std::map
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string

/*
 * Key differences between operator[] and insert():
 * - operator[] always overwrites existing values
 * - insert() preserves existing values
 * - insert() returns pair<iterator, bool>
 */

std::map<std::string, std::string> BuildMap(std::ifstream& map_file) {
  std::map<std::string, std::string> trans_map;  // holds the transformations
  std::string key;                               // a word to transform
  std::string value;                             // phrase to use instead
  // read the first word into key and the rest of the line into value
  while (map_file >> key && std::getline(map_file, value)) {
    if (value.size() > 1) {              // check that there is a transformation
      trans_map[key] = value.substr(1);  // skip leading space
    } else {
      throw std::runtime_error("no rule for " + key);
    }
  }
  return trans_map;
}

#endif  // CHAPTER_11_EXERCISE_35_H_