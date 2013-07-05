/*
 * Exercise 9.46: Rewrite the previous exercise using a position and length to
 * manage the strings. This time use only the insert function.
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Adds prefix and suffix to a name using only insert() with positions
 * @param name The original name
 * @param prefix The honorific prefix (e.g., "Mr.", "Ms.")
 * @param suffix The generational suffix (e.g., "Jr.", "III")
 * @return A new string with prefix and suffix added
 */
std::string FormatName(const std::string& name, const std::string& prefix,
                       const std::string& suffix) {
  std::string formatted_name = name;

  // Add prefix at position 0
  if (!prefix.empty()) {
    formatted_name.insert(0, prefix);
    // Add space if needed
    if (prefix.back() != ' ') {
      formatted_name.insert(prefix.length(), " ");
    }
  }

  // Add suffix at the end using insert at size()
  if (!suffix.empty()) {
    // Add space if needed
    if (suffix.front() != ' ') {
      formatted_name.insert(formatted_name.length(), " ");
    }
    formatted_name.insert(formatted_name.length(), suffix);
  }

  return formatted_name;
}

int main() {
  // Test cases
  std::cout << FormatName("John Doe", "Mr.", "Jr.") << "\n";
  // Output: "Mr. John Doe Jr."

  std::cout << FormatName("Smith", "Dr.", "PhD") << "\n";
  // Output: "Dr. Smith PhD"

  std::cout << FormatName("Alice", "Ms.", "") << "\n";
  // Output: "Ms. Alice"

  std::cout << FormatName("Johnson", "", "III") << "\n";
  // Output: "Johnson III"

  // Edge case - empty name
  std::cout << FormatName("", "Prof.", "") << "\n";
  // Output: "Prof. "

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-46.cc && ./main
 * Mr. John Doe Jr.
 * Dr. Smith PhD
 * Ms. Alice
 * Johnson III
 * Prof.
 */
