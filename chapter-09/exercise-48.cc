/*
 * Exercise 9.48: Given the definitions of name and numbers on page 365, what
 * does numbers.find(name) return?
 */

#include <iostream>  // std::cout
#include <string>    // std::string

int main() {
  std::string numbers("0123456789");
  std::string name("r2d2");

  size_t pos = numbers.find(name);

  if (pos == std::string::npos) {
    std::cout << "Substring '" << name << "' not found in '" << numbers
              << "'\n";
    std::cout << "Return value: " << pos << " (npos)\n";
  } else {
    std::cout << "Substring found at position: " << pos << "\n";
  }

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-48.cc && ./main
 * Substring 'r2d2' not found in '0123456789'
 * Return value: 18446744073709551615 (npos)
 */
