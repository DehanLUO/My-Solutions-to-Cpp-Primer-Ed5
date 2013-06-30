/*
 * Exercise 1.20: http://www.informit.com/title/0321714113 contains a copy of
 * Sales_item.h in the Chapter 1 code directory. Copy that file to your working
 * directory. Use it to write a program that reads a set of book sales
 * transactions, writing each transaction to the standard output.
 */

#include <iostream>  // std::cin, std::cout

#include "../include/Sales_item.h"  // Sales_item

int main() {
  Sales_item book;

  std::cout << "Enter sales data: \n";
  while (std::cin >> book) {
    std::cout << "isbn units_sold revenue avg_price: " << book << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main exercise01-20.cc && ./main
 * Enter sales data:
 * 0-201-70353-X 4 24.99
 * isbn units_sold revenue avg_price: 0-201-70353-X 4 99.96 24.99
 */