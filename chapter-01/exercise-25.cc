/*
 * Exercise 1.25: Using the Sales_item.h header from the Web site, compile and
 * execute the bookstore program presented in this section.
 */

#include <iostream>  // std::cin, std::cout, std::cerr

#include "../include/Sales_item.h"  // Sales_item

int main() {
  Sales_item total;  // variable to hold data for the next transaction
  // read the first transaction and ensure that there are data to process
  if (std::cin >> total) {
    Sales_item trans;  // variable to hold the running sum;

    // read and process the remaining transactions
    while (std::cin >> trans) {
      // if we are still processing the same book
      if (total.isbn() == trans.isbn()) {
        total += trans;  // update the running total
      } else {
        // print results for the previous book
        std::cout << total << std::endl;
        total = trans;  // total now refers to the next book
      }
    }
    std::cout << total << std::endl;  // print the last transaction
  } else {
    // no input! warn the user
    std::cerr << "No data?!" << std::endl;
    return -1;  // indicate failure
  }
  return 0;
}

/*
 * $ g++ -o main exercise-25.cc && ./main < ../data/book_sales
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 16 198 12.375
 * 0-399-82477-1 5 226.95 45.39
 * 0-201-78345-X 5 110 22
 */