/*
 * Exercise 14.36: Use the class from the previous exercise to read the standard
 * input, storing each line as an element in a vector.
 */

#include <iostream>  // std::cin, std::cout
#include <string>    //std::string
#include <vector>    // std::vector

#include "exercise-35.h"  // ReadString

/**
 * @brief Reads standard input and stores each line in a vector
 * @return std::vector<std::string> Vector containing all read lines
 * @note This function demonstrates the usage of ReadString functor to read
 * multiple lines from standard input and store them in a container.
 * The reading continues until end-of-file is encountered or an empty
 * string is returned indicating read failure.
 * @time Complexity O(n*m) where n is number of lines, m is average line length
 * @space Complexity O(n*m) for storing all lines in memory
 */
std::vector<std::string> ReadInputToVector() {
  std::vector<std::string> lines;
  ReadString reader;  // Default constructor uses std::cin

  /*
   * The ReadString functor returns an empty string when input fails,
   * which serves as our termination condition for the reading loop.
   * This approach handles both manual termination (Ctrl+D on Unix,
   * Ctrl+Z on Windows) and actual end-of-file conditions.
   */
  while (true) {
    std::string line = reader();
    if (line.empty()) {
      /*
       * An empty string indicates either intentional empty input
       * or read failure. In this context, we use it as the loop
       * termination condition as specified by the exercise.
       */
      break;
    }
    lines.push_back(line);
  }

  return lines;
}

int main() {
  /*
   * Display instructions to the user about the input process.
   * This enhances user experience by providing clear guidance.
   */
  std::cout << "Enter text lines (Ctrl+D/Ctrl+Z to end input):\n";

  std::vector<std::string> input_lines = ReadInputToVector();

  /*
   * Output the results to demonstrate successful storage.
   * The size() member function provides the number of elements,
   * allowing us to verify that all input was captured correctly.
   */
  std::cout << "\nSuccessfully read " << input_lines.size() << " lines:\n";

  /*
   * Iterate through the vector and print each stored line.
   * Using range-based for loop with const reference avoids
   * unnecessary copies while maintaining read-only access.
   */
  for (const auto& line : input_lines) {
    std::cout << line << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-36.cc && ./main
 * Enter text lines (Ctrl+D/Ctrl+Z to end input):
 * Hello
 * World
 * Successfully read 2 lines:
 * Hello
 * World
 */
