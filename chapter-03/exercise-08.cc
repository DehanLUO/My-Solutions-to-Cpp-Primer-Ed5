/*
 * Exercise 3.8: Rewrite the program in the first exercise, first using a while
 * and again using a traditional for loop. Which of the three approaches do you
 * prefer and why?
 */

#include <iostream>  // std::getline, std::cout
#include <string>    // std::string

int main() {
  std::string str;
  std::cout << "Enter a string: ";
  std::getline(std::cin, str);  // Read the entire line including whitespace

  // using a while
  {
    decltype(str.size()) index = 0, size = str.size();
    while (index < size) {
      str[index++] = 'X';
    }
    std::cout << "Modified string using a while:\n" << str << '\n';
  }

  // using a traditional for loop
  {
    decltype(str.size()) index = 0, size = str.size();
    for (; index < size; ++index) {
      str[index] = 'x';  // X->x
    }
    std::cout << "Modified string using a traditional for loop:\n"
              << str << '\n';
  }

  return 0;
}

/*
 * The range-for loop is ideal for this task for its cleanest syntax, no manual
 * index management, and safest (no off-by-one risk).
 */

/*
 * $ g++ -o main exercise-08.cc && ./main
 * Enter a string: The quick brown fox jumps over the lazy dog.
 * Modified string using a while:
 * XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
 * Modified string using a traditional for loop
 * xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 */