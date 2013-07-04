/*
 * Exercise 7.41: Rewrite your own version of the Sales_data class to use
 * delegating constructors. Add a statement to the body of each of the
 * constructors that prints a message whenever it is executed. Write
 * declarations to construct a Sales_data object in every way possible. Study
 * the output until you are certain you understand the order of execution among
 * delegating constructors.
 */

#include "exercise-41.h"  // Sales_data

#include <iostream>  // std::cout

int main() {
  std::cout << "Sales_data():\n";
  Sales_data();

  std::cout << "\nSales_data(const std::string& book_nombre):\n";
  Sales_data("0-201-70353-X");

  std::cout << "\nSales_data(const std::string& book_nombre, uint16_t "
               "units_sold, float revenue)\n";
  Sales_data("0-201-82470-1", 4, 24.99);

  return 0;
}

/* $ g++ -o main chapter-07/exercise-41.cc && ./main
 * Sales_data():
 * Sales_data(const std::string& book_nombre=, uint16_t units_sold=0, revenue=0)
 * Sales_data()
 * 
 * Sales_data(const std::string& book_nombre):
 * Sales_data(const std::string& book_nombre=0-201-70353-X, uint16_t units_sold=0, revenue=0)
 * Sales_data(const std::string& book_nombre=0-201-70353-X)
 * 
 * Sales_data(const std::string& book_nombre, uint16_t units_sold, float revenue)
 * Sales_data(const std::string& book_nombre=0-201-82470-1, uint16_t units_sold=4, revenue=24.99)
 */
