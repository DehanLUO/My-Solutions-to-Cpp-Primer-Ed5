/*
 * Exercise 6.16: The following function, although legal, is less useful than it
 * might be. Identify and correct the limitation on this function:
 *     bool is_empty(string& s) { return s.empty(); }
 */

#include <string>  // std::string

/**
 * @brief Checks if a string is empty
 * @param s The string to check (now const reference)
 * @return bool True if string is empty, false otherwise
 *
 * Improvements:
 * 1. Made parameter const reference
 * 2. Can now accept const strings and temporaries
 * 3. More flexible usage
 */
bool IsEmpty(const std::string& s) { return s.empty(); }

/*
 * Original Problems:
 * 1. Non-const reference parameter prevented:
 *    - Passing const strings
 *    - Passing string literals
 *    - Passing temporary strings
 * 2. Unnecessarily restricted usage
 *
 * Corrected Version Benefits:
 * 1. Works with all string types
 * 2. Maintains efficiency (no copying)
 * 3. Clearly expresses read-only intent
 */

int main() {
  std::string s1 = "hello";
  const std::string s2 = "world";

  // Now works with all these cases:
  bool b1 = IsEmpty(s1);             // modifiable string
  bool b2 = IsEmpty(s2);             // const string
  bool b3 = IsEmpty("");             // string literal
  bool b4 = IsEmpty(std::string());  // temporary

  return 0;
}
