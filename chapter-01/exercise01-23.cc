/*
 * Exercise 1.23: Write a program that reads several transactions and counts how
 * many transactions occur for each ISBN.
 */

#include <iostream>  // std::cin, std::cout, std::cerr

#include "../include/Sales_item.h"  // Sales_item

int main() {
  Sales_item sales_base;  // Holds the current ISBN group to compare against

  std::cout << "Enter some sales records:\n";
  // Read first record as the base case
  if (std::cin >> sales_base) {
    Sales_item current_sales_record;  // Reads each incoming transaction
    int count = 1;  // Tracks number of records in current ISBN group

    // Process subsequent records
    while (std::cin >> current_sales_record) {
      if (compareIsbn(sales_base, current_sales_record)) {
        ++count;  // Increment if same ISBN as base
      } else {
        // Output stats for previous ISBN group
        std::cout << sales_base.isbn() << " has " << count
                  << " sales records\n";
        sales_base = current_sales_record;  // Start new ISBN group
        count = 1;                          // Reset counter
      }
    }
    // Output the last ISBN group
    std::cout << sales_base.isbn() << " has " << count << " sales records\n";
  } else {
    std::cerr << "No sales records\n";  // Handle empty input case
    return -1;
  }
  return 0;
}

/*
 * $ g++ -o main exercise01-23.cc && ./main
 * Enter some sales records:
 * 0-201-78345-X 3 20.00
 * 0-201-78345-X 2 25.00
 * 0-201-78345-X 5 50.00
 * 0-201-78345-Y 1 100.00
 * 0-201-78345-X has 3 sales records
 * 0-201-78345-Y 2 200.00
 * 0-201-78345-Y has 2 sales records
 */