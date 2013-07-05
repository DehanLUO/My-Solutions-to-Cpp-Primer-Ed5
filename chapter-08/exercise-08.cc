/*
 * Exercise 8.8: Revise the program from the previous exercise to append its
 * output to its given file. Run the program on the same output file at least
 * twice to ensure that the data are preserved.
 */

#include <cstdlib>   // EXIT_FAILURE
#include <fstream>   // std::ifstream, std::ofstream
#include <iostream>  // std::cout, std::cerr
#include <string>    // std::string

#include "exercise-06.h"  // Sales_data

/**
 * @brief Processes transactions from input file
 * @param input_filename Path to transaction file
 * @param output_filename Path to output
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int ProcessTransactions(const std::string& input_filename,
                        const std::string& output_filename) {
  std::ifstream input(input_filename);
  if (!input) {
    std::cerr << "Error: Could not open file " << input_filename << '\n';
    return EXIT_FAILURE;  // indicate failure
  }

  std::ofstream output(output_filename,
                       std::ofstream::out | std::ofstream::app);
  if (!output) {
    std::cerr << "Error: Could not open file " << output_filename << '\n';
    return EXIT_FAILURE;
  }

  Sales_data total;  // variable to hold for the next transaction

  // read the first transaction and ensure that there are data to process
  if (!total.Input(input)) {
    // no input! warn the user
    std::cerr << "No data?!\n";
    return EXIT_FAILURE;
  }

  Sales_data trans;  // variable to hold the running sum
  while (trans.Input(input)) {
    // if we are still processing the same book
    if (total.book_nombre == trans.book_nombre) {
      total.Combine(trans);
    } else {
      // print results for the previous book
      total.Dump(output) << '\n';
      total = trans;  // total now refers to the next book
    }
  }
  total.Dump(output) << '\n';  // print the last transaction

  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <filename> <filename>\n";
    return EXIT_FAILURE;
  }

  return ProcessTransactions(argv[1], argv[2]);
}

/*
 * $ g++ -o main chapter-08/exercise-08.cc \
 * && ./main data/book_sales ./output_2.txt \
 * && ./main data/book_sales ./output_2.txt \
 * && cat output_2.txt
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 16 198 12.375
 * 0-399-82477-1 5 226.95 45.39
 * 0-201-78345-X 5 110 22
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 16 198 12.375
 * 0-399-82477-1 5 226.95 45.39
 * 0-201-78345-X 5 110 22
 */
