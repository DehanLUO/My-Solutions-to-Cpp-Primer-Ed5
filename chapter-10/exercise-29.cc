/*
 * Exercise 10.29: Write a program using stream iterators to read a text file
 * into a vector of strings.
 */

#include <fstream>   // std::ifstream
#include <iostream>  // std::cout, std::cerr
#include <iterator>  // std::istream_iterator
#include <string>    // std::string
#include <vector>    // std::vector

/**
 * @brief Reads a text file into a vector of strings using stream iterators
 * @param filename The name of the file to read
 * @return Vector containing all words from the file
 */
std::vector<std::string> ReadFileToVector(const std::string& filename) {
  std::ifstream in(filename);
  if (!in) {
    std::cerr << "Error opening file: " << filename << '\n';
    return {};
  }

  // Create vector from stream iterators
  return {std::istream_iterator<std::string>(in),
          std::istream_iterator<std::string>()};
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  auto words = ReadFileToVector(argv[1]);

  // Print results
  std::cout << "Read " << words.size() << " words from file:\n";
  for (const auto& word : words) {
    std::cout << word << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-29.cc && ./main data/sstream
 * Read 9 words from file:
 * morgan
 * 2015552368
 * 8625550123
 * drew
 * 9735550130
 * lee
 * 6095550132
 * 2015550175
 * 8005550000
 */
