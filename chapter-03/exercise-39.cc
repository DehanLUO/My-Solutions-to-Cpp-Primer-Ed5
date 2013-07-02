/*
 * Exercise 3.39: Write a program to compare two strings. Now write a program to
 * compare the values of two C-style character strings.
 */

#include <cstring>   // strcmp
#include <ios>       // std::boolalpha
#include <iostream>  // std::cout
#include <string>    // std::string

int main() {
  std::cout << std::boolalpha;
  /*
   * Comparing c++ std::string
   */
  {
    std::string str1 = "hello";
    std::string str2 = {'h', 'e', 'l', 'l', 'o'};
    std::string str3 = "Hello";

    // Using == operator
    std::cout << "str1 == str2: " << (str1 == str2) << '\n';
    std::cout << "str1 == str3: " << (str1 == str3) << '\n';
  }

  /*
   * Comparing c-stype strings
   */
  {
    const char cstr1[] = "hello";
    const char cstr2[] = {'h', 'e', 'l', 'l', 'o'};
    const char cstr3[] = {'h', 'e', 'l', 'l', 'o', '\0'};

    /*
     * Comparing cstr1 vs cstr2 is undefined behaviour. cstr1 = "hello" (auto
     * null-terminated). Actually stored as {'h', 'e', 'l', 'l', 'o', '\0'};
     * cstr2 missing null terminator. strcmp() keeps reading past the array
     * until it randomly finds a '\0' -> UB!
     */
    std::cout << "cstr1 vs cstr2: " << strcmp(cstr1, cstr2) << '\n';

    std::cout << "cstr1 vs cstr3: " << strcmp(cstr1, cstr3) << '\n';
  }

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-39.cc && ./main
 * str1 == str2: true
 * str1 == str3: false
 * cstr1 vs cstr2: -104
 * cstr1 vs cstr3: 0
 */