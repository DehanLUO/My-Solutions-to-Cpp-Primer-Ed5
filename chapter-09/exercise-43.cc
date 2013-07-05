/*
 * Exercise 9.43: Write a function that takes three strings, s, oldVal, and
 * newVal. Using iterators, and the insert and erase functions replace all
 * instances of oldVal that appear in s by newVal. Test your function by using
 * it to replace common abbreviations, such as "tho" by "though" and "thru" by
 * "through".
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Replaces all occurrences of old_val in s with new_val
 * @param s The string to modify
 * @param old_val The substring to replace
 * @param new_val The replacement substring
 *
 * Uses string iterators with insert and erase
 * Handles overlapping matches correctly
 */
void ReplaceAll(std::string& s, const std::string& old_val,
                const std::string& new_val) {
  if (old_val.empty()) return;  // handle empty oldVal case

  auto it = s.begin();
  while (it <= s.end() - old_val.size()) {
    if (std::string(it, it + old_val.size()) == old_val) {
      // Replace found substring
      it = s.erase(it, it + old_val.size());
      it = s.insert(it, new_val.begin(), new_val.end());
      it += new_val.size();  // skip past the newVal we just inserted
    } else {
      ++it;
    }
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
 * $ g++ -o main chapter-09/exercise-43.cc && ./main
 * though this is though, and through that is through
 * hi world hi
 * XbXb
 */
