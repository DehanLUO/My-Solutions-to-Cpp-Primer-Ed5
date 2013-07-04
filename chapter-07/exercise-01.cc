/*
 * Exercise 7.1: Write a version of the transaction-processing program from
 * § 1.6 (p. 24) using the Sales_data class you defined for the exercises in
 * § 2.6.1 (p. 72).
 */

#include <iostream>  // std::cerr

#include "../chapter-02/exercise-40.h"  // Sales_data

int main() {
  Sales_data total;  // variable to hold for the next transaction

  // read the first transaction and ensure that there are data to process
  if (total.Input()) {
    Sales_data trans;  // variable to hold the running sum
    while (trans.Input()) {
      // if we are still processing the same book
      if (total.book_nombre == trans.book_nombre) {
        total.revenue += trans.revenue;
        total.units_sold += trans.units_sold;
      } else {
        // print results for the previous book
        total.Dump();
        total.book_nombre = trans.book_nombre;
        total.revenue = trans.revenue;
        total.units_sold = trans.units_sold;
        // total now refers to the next book
      }
    }
    total.Dump();  // print the last transaction
  } else {
    // no input! warn the user
    std::cerr << "No data?!\n";
    return -1;  // indicate failure
  }
  return 0;
}

/* $ g++ -o main chapter-07/exercise-01.cc && ./main < data/book_sales
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 16 198 12.375
 * 0-399-82477-1 5 226.95 45.39
 * 0-201-78345-X 5 110 22
 */
