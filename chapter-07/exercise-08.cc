/*
 * Exercise 7.8: Why does read define its Sales_data parameter as a plain
 * reference and print define its parameter as a reference to const?
 * // input transactions contain ISBN, number of copies sold, and sales price
 * istream &read(istream &is ,Sales_data &item) {
 *   double price = 0;
 *   is >> item.bookNo >> item.units_sold >> price;
 *   item.revenue = price * item.units_sold;
 *   return is;
 * }
 * ostream &print(ostream &os, const Sales_data &item) {
 *   os << ite.isbn() << " " << item.units_sold << " "
 *      << item.revenue << " " << item.avg_price();
 *   return os;
 * }
 */

#include <iostream>  // std::istream, std::ostream
#include <string>    // std::string

struct Sales_data {
  std::string bookNo;
  unsigned units_sold;
  double revenue;

  /**
   * @brief Calculates average price per unit
   * @return Double representing mean price
   */
  double avg_price() const;
};

/*
 * Input operation parameter explanation:
 * 1. Non-const reference for Sales_data because:
 *    - Modifies all data members (bookNo, units_sold, revenue)
 *    - Needs write access to populate object fields
 * 2. Non-const reference for istream because:
 *    - Stream state changes during extraction
 *    - Must be able to modify stream's error state flags
 */
std::istream& Read(std::istream& is, Sales_data& item) {
  double price = 0.0;
  is >> item.bookNo >> item.units_sold >> price;
  item.revenue = price * item.units_sold;
  return is;
}

/*
 * Output operation parameter explanation:
 * 1. Const reference for Sales_data because:
 *    - Only reads member data (no modification needed)
 *    - Safe for temporary objects
 *    - Enables usage with const Sales_data objects
 * 2. Non-const reference for ostream because:
 *    - Stream state changes during insertion
 *    - Must be able to modify stream's error state flags
 */
std::ostream& Print(std::ostream& os, const Sales_data& item) {
  os << item.bookNo << " " << item.units_sold << " " << item.revenue << " "
     << item.avg_price();
  return os;
}

double Sales_data::avg_price() const {
  return units_sold ? revenue / units_sold : 0.0;
}

/*
 * Demonstration of proper usage:
 * 1. Shows const and non-const scenarios
 * 2. Illustrates stream state modification
 */
int main() {
  Sales_data current_sale;

  // Requires non-const reference for modification
  Read(std::cin, current_sale);

  // Works with const reference (Print doesn't modify)
  const Sales_data const_sale = current_sale;
  Print(std::cout, const_sale) << '\n';

  return 0;
}
