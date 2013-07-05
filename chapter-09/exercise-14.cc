/*
 * Exercise 9.14: Write a program to assign the elements from a list of
 * char* pointers to C-style character strings to a vector of strings.
 */

#include <algorithm>  // std::transform
#include <iostream>   // std::cout
#include <list>       // std::list
#include <string>     // std::string
#include <vector>     // std::vector

/**
 * @brief Assigns elements from list<char*> to vector<string>
 *
 * Demonstrates three approaches:
 * 1. Range constructor with implicit conversion
 * 2. transform algorithm with explicit conversion
 * 3. Range-based for loop with push_back
 */
void DemonstrateConversion() {
  // Source data
  const char* cstrs[] = {"Hello", "World", "C++", "Programming"};
  std::list<const char*> char_list(cstrs, cstrs + 4);

  // Method 1: Range constructor (implicit conversion)
  std::vector<std::string> str_vec1(char_list.begin(), char_list.end());

  // Method 2: transform with explicit conversion
  std::vector<std::string> str_vec2;
  str_vec2.reserve(char_list.size());
  std::transform(char_list.begin(), char_list.end(),
                 std::back_inserter(str_vec2),
                 [](const char* cstr) { return std::string(cstr); });

  // Method 3: Range-based for loop
  std::vector<std::string> str_vec3;
  for (const char* cstr : char_list) {
    str_vec3.push_back(cstr);
  }

  // Print results
  auto print_vector = [](const std::vector<std::string>& vec) {
    for (const auto& str : vec) {
      std::cout << str << ' ';
    }
    std::cout << '\n';
  };

  std::cout << "Method 1: ";
  print_vector(str_vec1);  // Hello World C++ Programming

  std::cout << "Method 2: ";
  print_vector(str_vec2);  // Hello World C++ Programming

  std::cout << "Method 3: ";
  print_vector(str_vec3);  // Hello World C++ Programming
}

int main() {
  DemonstrateConversion();
  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-14.cc && ./main
 * Method 1: Hello World C++ Programming
 * Method 2: Hello World C++ Programming
 * Method 3: Hello World C++ Programming
 */
