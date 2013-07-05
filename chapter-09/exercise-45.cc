/*
 * Exercise 9.45: Write a funtion that takes a string representing a name and
 * two other strings representing a prefix, such as "Mr." or "Ms." and a suffix,
 * such as "Jr." or "III". Using iterators and the insert and append functions,
 * generate and return a new string with the suffix and prefix added to the
 * given name.
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Adds prefix and suffix to a name using string operations
 * @param name The original name
 * @param prefix The honorific prefix (e.g., "Mr.", "Ms.")
 * @param suffix The generational suffix (e.g., "Jr.", "III")
 * @return A new string with prefix and suffix added
 */
std::string FormatName(const std::string& name, const std::string& prefix,
                       const std::string& suffix) {
  std::string formatted_name = name;

  // Add prefix at the beginning using insert
  if (!prefix.empty()) {
    formatted_name.insert(formatted_name.begin(), prefix.begin(), prefix.end());
    // Add space after prefix if needed
    if (prefix.back() != ' ') {
      formatted_name.insert(formatted_name.begin() + prefix.size(), ' ');
    }
  }

  // Add suffix at the end using append
  if (!suffix.empty()) {
    // Add space before suffix if needed
    if (suffix.front() != ' ') {
      formatted_name.append(" ");
    }
    formatted_name.append(suffix);
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
 * $ g++ -o main chapter-09/exercise-45.cc && ./main
 * Mr. John Doe Jr.
 * Dr. Smith PhD
 * Ms. Alice
 * Johnson III
 * Prof.
 */
