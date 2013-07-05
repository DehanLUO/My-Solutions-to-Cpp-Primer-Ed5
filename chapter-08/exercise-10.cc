/*
 * Exercise 8.10: Write a program to store each line from a file in a
 * vector<string>. Now use an istringstream to read each element from the vector
 * a word at a time.
 */

#include <cstdlib>       // EXIT_FAILURE
#include <fstream>       // std::ifstream
#include <iostream>      // std::cout, std::cerr
#include <sstream>       // std::istringstream
#include <string>        // std::string
#include <system_error>  // std::error_code
#include <vector>        // std::vector

/**
 * @brief Reads file contents into vector of strings
 * @param filename Path to input file
 * @param output Vector to store lines
 * @return std::error_code indicating operation status
 *
 * Features:
 * - Preserves original vector contents on failure
 * - Detailed error reporting
 * - RAII file handle management
 * - Efficient memory allocation
 */
std::error_code ReadFileToVector(const std::string& filename,
                                 std::vector<std::string>& output) {
  std::ifstream input(filename, std::ifstream::in);
  if (!input) {
    return std::make_error_code(static_cast<std::errc>(errno));
  }

  try {
    std::vector<std::string> local_vec;
    local_vec.reserve(100);  // Preallocate for typical files

    std::string line;
    while (std::getline(input, line)) {
      local_vec.emplace_back(std::move(line));
    }

    if (!input.eof() && input.fail()) {
      return std::make_error_code(std::errc::io_error);
    }

    output = std::move(local_vec);
    return {};
  } catch (...) {
    return std::make_error_code(std::errc::not_enough_memory);
  }
}

/**
 * @brief Processes each line to extract words
 * @param lines Vector containing file lines
 */
void ProcessLinesToWords(const std::vector<std::string>& lines) {
  for (const auto& line : lines) {
    std::istringstream iss(line);  // bind iss to the line we just read
    std::string word;

    while (iss >> word) {  // read the word
      std::cout << word << ' ';
    }
    std::cout << '\n';
  }
}

/**
 * @brief Demonstrates file reading functionality
 */
void DemonstrateFileReading(const std::string& filename) {
  std::vector<std::string> lines;
  if (auto ec = ReadFileToVector(filename, lines)) {
    std::cerr << "Error reading file: " << ec.message() << '\n';
    return;
  }

  ProcessLinesToWords(lines);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  DemonstrateFileReading(argv[1]);

  return EXIT_SUCCESS;
}

/*
 * $ g++ -o main chapter08/exercise-10.cc && ./main
 * 0-201-70353-X 4 24.99
 * 0-201-82470-1 4 45.39
 * 0-201-88954-4 2 15.00
 * 0-201-88954-4 5 12.00
 * 0-201-88954-4 7 12.00
 * 0-201-88954-4 2 12.00
 * 0-399-82477-1 2 45.39
 * 0-399-82477-1 3 45.39
 * 0-201-78345-X 3 20.00
 * 0-201-78345-X 2 25.00
 */
