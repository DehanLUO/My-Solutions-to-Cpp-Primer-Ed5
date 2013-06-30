/*
 * Exercise 1.21: Write a program that reads two Sales_item objects that have
 * the same ISBN and produces their sum.
 */

#include <iostream>  // std::cin, std::cout, std::cerr

#include "../include/Sales_item.h"  // Sales_item

int main() {
  Sales_item sales_item_a;
  Sales_item sales_item_b;

  std::cout << "Enter two sales records with the same ISBN:\n";
  std::cin >> sales_item_a >> sales_item_b;
  if (compareIsbn(sales_item_a, sales_item_b)) {
    std::cout << "Summary: ISBN, quantity sold, total sales revenue, and "
                 "average selling price:\n"
              << sales_item_a + sales_item_b << '\n';
  } else {
    std::cerr << "ISBNs do not match\n";
  }

  return 0;
}

/*
 * $ g++ -o main exercise01-21.cc && ./main
 * Enter two sales records with the same ISBN:
 * 0-201-78345-X 3 20.00
 * 0-201-78345-X 2 25.00
 * Summary: ISBN, quantity sold, total sales revenue, and average selling price:
 * 0-201-78345-X 5 110 22
 */