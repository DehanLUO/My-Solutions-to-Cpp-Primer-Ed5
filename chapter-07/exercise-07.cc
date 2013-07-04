/*
 * Exercise 7.7: Rewrite the transaction-processing program you wrote for the
 * exercises in § 7.1.2 (p. 260) to use these new functions.
 */

#include <iostream>  // std::cout, std::cin, std::cerr

#include "exercise-06.h"  // Sales_data

int main() {
  Sales_data total;  // variable to hold for the next transaction

  // read the first transaction and ensure that there are data to process
  if (total.read(std::cin)) {
    Sales_data trans;  // variable to hold the running sum
    while (trans.read(std::cin)) {
      // if we are still processing the same book
      if (total.isbn() == trans.isbn()) {
        total.combine(trans);
      } else {
        // print results for the previous book
        total.print(std::cout);
        total = trans;
        // total now refers to the next book
      }
    }
    total.print(std::cout);  // print the last transaction
  } else {
    // no input! warn the user
    std::cerr << "No data?!\n";
    return -1;  // indicate failure
  }
  return 0;
}

/* $ g++ -o main chapter-07/exercise-03.cc && ./main  < data/book_sales
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 16 198 12.375
 * 0-399-82477-1 5 226.95 45.39
 * 0-201-78345-X 5 110 22
 */
