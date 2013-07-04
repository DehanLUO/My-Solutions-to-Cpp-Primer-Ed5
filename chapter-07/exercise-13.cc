/*
 * Exercise 7.13: Rewrite the program from page 255 to use the istream
 * constructor.
 */

#include <iostream>  // std::cin, std::cout, std::cerr

#include "exercise-12.h"  // Sales_data

int main() {
  Sales_data total;            // variable to hold the running sum
  if (total.read(std::cin)) {  // read the first transaction
    Sales_data trans;          // variable to hold data for the next transaction
    while (trans.read(std::cin)) {         // read the remaining transaction
      if (total.isbn() == trans.isbn()) {  // check the isbns
        total.combine(trans);              // update the running total
      } else {
        total.print(std::cout) << '\n';  // print the results
        total = trans;                   // process the next book
      }
    }
    total.print(std::cout) << '\n';  // print the last transaction
  } else {                           // there was no input
    std::cerr << "No data?!\n";      // notify the user
  }
}

/* $  g++ -o main chapter-07/exercise-13.cc  && ./main < data/book_sales
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 16 198 12.375
 * 0-399-82477-1 5 226.95 45.39
 * 0-201-78345-X 5 110 22
 */
