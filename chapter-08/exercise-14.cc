/*
 * Exercise 8.14: Why did we declare entry and nums as const auto &?
 */

#include <fstream>   // std::ifstream
#include <iostream>  // std::cin
#include <sstream>   // std::istringstream, std::ostringstream
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

bool valid(const std::string& num) { return true; }
std::string format(const std::string& nums) { return nums; }

/**
 * @brief Prints formatted phone records
 * @param records Vector of PersonInfo to print
 */
void PrintPhoneRecords(const std::vector<PersonInfo>& people) {
  /**
   * @brief Rationale for const auto& usage
   *
   * 1. For entry in people:
   *    - const: Ensures PersonInfo objects aren't modified
   *    - auto&: Avoids copying while allowing access to members
   *    - Combined: Efficient read-only access to elements
   *
   * 2. For nums in entry.phones:
   *    - const: Phone numbers shouldn't be modified
   *    - auto&: Avoids copying strings
   *    - Combined: Optimal for string view operations
   */
  for (const auto& entry : people) {         // for each entry in people
    std::ostringstream formatted, badNums;   // objects created on each loop
    for (const auto& nums : entry.phones) {  // for each number
      if (!valid(nums)) {
        badNums << ' ' << nums;  // string in badNums;
      } else {
        // "writes"  to formatted's string
        formatted << ' ' << format(nums);
      }
    }
    if (badNums.str().empty()) {             // there were no bad numbers
      std::cout << entry.name << ' '         // print the name
                << formatted.str() << '\n';  // and reformatted numbers
    } else {  // otherwise, print the name and bad numbers
      std::cerr << "input error: " << entry.name << " invalid number(s) "
                << badNums.str() << '\n';
    }
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

/*
 * $ g++ -o main chapter08/exercise-14.cc && ./main  data/sstream
 * morgan  2015552368 8625550123
 * drew  9735550130
 * lee  6095550132 2015550175 8005550000
 */
