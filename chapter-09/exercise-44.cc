/*
 * Exercise 9.44: Rewrite the previous function using an index and replace.
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Replaces all occurrences of old_val in s with new_val using index and
 * replace
 * @param s The string to modify
 * @param old_val The substring to replace
 * @param new_val The replacement substring
 */
void ReplaceAll(std::string& s, const std::string& old_val,
                const std::string& new_val) {
  if (old_val.empty()) return;

  size_t pos = 0;
  while ((pos = s.find(old_val, pos)) != std::string::npos) {
    s.replace(pos, old_val.length(), new_val);
    pos += new_val.length();  // Skip past the replacement
  }
}

int main() {
  // Test cases
  std::string s1 = "tho this is tho, and thru that is thru";
  ReplaceAll(s1, "tho", "though");
  ReplaceAll(s1, "thru", "through");
  std::cout << s1
            << "\n";  // "though this is though, and through that is through"

  std::string s2 = "hello world hello";
  ReplaceAll(s2, "hello", "hi");
  std::cout << s2 << "\n";  // "hi world hi"

  std::string s3 = "abababab";
  ReplaceAll(s3, "aba", "X");
  std::cout << s3 << "\n";  // "XbXb" (handles overlapping matches)

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-44.cc && ./main
 * though this is though, and through that is through
 * hi world hi
 * XbXb
 */
