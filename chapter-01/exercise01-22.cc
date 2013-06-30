/*
 * Exercise 1.22: Write a program that reads several transactions for the same
 * ISBN. Write the sum of all the transactions that were read.
 */

#include <iostream>  // std::cin, std::cout, std::cerr

#include "../include/Sales_item.h"  // Sales_item

int main() {
  Sales_item total;
  Sales_item sales_item;

  std::cout << "Enter some sales records with the same ISBN:\n";
  if (!(std::cin >> total)) {
    std::cerr << "Invalid data!\n";
    return -1;
  }

  while (std::cin >> sales_item) {
    if (compareIsbn(sales_item, total)) {  // same ISBN
      total += sales_item;
    } else {  // different ISBN
      std::cerr << "ISBNs do not match\n";
      return -1;
    }
  }

  std::cout << "Summary: ISBN, quantity sold, total sales revenue, and "
               "average selling price:\n"
            << total << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise01-22.cc && ./main
 * Enter some sales records with the same ISBN:
 * 0-201-78345-X 3 20.00
 * 0-201-78345-X 2 25.00
 * 0-201-78345-X 5 50.00
 * Summary: ISBN, quantity sold, total sales revenue, and average selling price:
 * 0-201-78345-X 10 360 36
 */