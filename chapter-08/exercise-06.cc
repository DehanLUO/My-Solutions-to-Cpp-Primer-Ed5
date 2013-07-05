/*
 * Exercise 8.6: Rewrite the bookstore program from § 7.1.1 (p. 256) to read its
 * transactions from a file. Pass the name of the file as an argument to main
 * (§ 6.2.5, p. 218).
 */

#include "exercise-06.h"  // Sales_data

#include <cstdlib>   // EXIT_FAILURE
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout, std::cerr
#include <string>    // std::string

/**
 * @brief Processes transactions from input file
 * @param filename Path to transaction file
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int ProcessTransactions(const std::string& filename) {
  std::ifstream input(filename);
  if (!input) {
    std::cerr << "Error: Could not open file " << filename << '\n';
    return EXIT_FAILURE;  // indicate failure
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
      total.Dump(std::cout) << '\n';
      total = trans;  // total now refers to the next book
    }
  }
  total.Dump(std::cout) << '\n';  // print the last transaction

  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  return ProcessTransactions(argv[1]);
}

/*
 * $ g++ -o main chapter08/exercise-06.cc && ./main data/book_sales
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 16 198 12.375
 * 0-399-82477-1 5 226.95 45.39
 * 0-201-78345-X 5 110 22
 */
