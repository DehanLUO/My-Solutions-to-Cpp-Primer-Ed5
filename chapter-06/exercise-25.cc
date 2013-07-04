/*
 * Exercise 6.25: Write a main function that takes two arguments. Concatenate
 * the supplied arguments and print the resulting string.
 */

#include <iostream>  // std::cout
#include <string>    // std::string

int main(int argc, char* argv[]) {
  // Check if we received exactly two arguments (plus program name)
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <string1> <string2>\n";
    return 1;
  }

  // Concatenate the two arguments
  std::string result = std::string(argv[1]) + argv[2];

  // Print the result
  std::cout << "Concatenated result: " << result << '\n';

  return 0;
}

/* $ g++ -o main chapter-06/exercise-25.cc && ./main "Hello " "World!"
 * Concatenated result: Hello World!
 */