/*
 * Exercise 8.13: Rewrite the phone number program from this section to read
 * from a named file rather than from cin.
 */

#include <fstream>   // std::ifstream
#include <iostream>  // std::cin
#include <sstream>   // std::istringstream
#include <string>    // std::string
#include <vector>    // std::vector

#include "exercise-12.h"  // PersonInfo

/**
 * @brief Reads phone records from file into vector
 * @param filename Input file path
 * @param output Vector to store records
 * @return std::error_code indicating status
 */
std::error_code ReadPhoneRecords(const std::string& filename,
                                 std::vector<PersonInfo>& output) {
  std::ifstream input(filename, std::ifstream::in);
  if (!input) {
    return std::make_error_code(static_cast<std::errc>(errno));
  }

  try {
    std::vector<PersonInfo>
        local_vec;           // will hold all the records from the input
    local_vec.reserve(100);  // Preallocate for typical files

    std::string line;  // will hold a line and word from input, respectively
    std::string word;

    while (std::getline(input, line)) {
      PersonInfo info;  // create an object to hold this record's data
      std::istringstream record(line);  // bind record to the line we just read

      record >> info.name;            // read the name
      while (record >> word) {        // read the phone numbers
        info.phones.push_back(word);  // and store them
      }

      local_vec.emplace_back(std::move(info));  // append this record
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
 * @brief Prints formatted phone records
 * @param records Vector of PersonInfo to print
 */
void PrintPhoneRecords(const std::vector<PersonInfo>& records) {
  for (const auto& person : records) {
    std::cout << "Name: " << person.name << "\nPhones: ";
    for (const auto& phone : person.phones) {
      std::cout << phone << " ";
    }
    std::cout << "\n\n";
  }
}

/**
 * @brief Demonstrates file reading functionality
 */
void DemonstrateFileReading(const std::string& filename) {
  std::vector<PersonInfo> peoples;
  if (auto ec = ReadPhoneRecords(filename, peoples)) {
    std::cerr << "Error reading file: " << ec.message() << '\n';
    return;
  }

  PrintPhoneRecords(peoples);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  DemonstrateFileReading(argv[1]);

  return EXIT_SUCCESS;
}

/* $ g++ -o main chapter-08/exercise-13.cc && ./main data/sstream
 * Name: morgan
 * Phones: 2015552368 8625550123
 *
 * Name: drew
 * Phones: 9735550130
 *
 * Name: lee
 * Phones: 6095550132 2015550175 8005550000
 */
