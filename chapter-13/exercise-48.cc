/*
 * Exercise 13.48: Define a vector<String> and call push_back several times on
 * that vector. Run your program and see how often Strings are copied.
 */

#include <vector>  // std::vector

#include "exercise-47.h"  // my::String

int main() {
  std::vector<my::String> svec;
  /*
   * Each push_back may trigger reallocation when:
   * - Capacity is exceeded
   * - Requires element migration to new storage
   */
  for (size_t i = 0; i < 5; ++i) {
    /*
     * Conversion chain:
     * 1. std::to_string creates temporary std::string
     * 2. c_str() provides C-style string pointer
     * 3. my::String constructor allocates new storage
     */
    svec.push_back(std::to_string(i).c_str());
  }

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-48.cc && ./main
 * String(const_pointer str):0
 * String(const String& other):0
 * String(const_pointer str):1
 * String(const String& other):1
 * String(const String& other):0
 * String(const_pointer str):2
 * String(const String& other):2
 * String(const String& other):0
 * String(const String& other):1
 * String(const_pointer str):3
 * String(const String& other):3
 * String(const_pointer str):4
 * String(const String& other):4
 * String(const String& other):0
 * String(const String& other):1
 * String(const String& other):2
 * String(const String& other):3
 */
