/*
 * Exercise 8.6: Rewrite the bookstore program from § 7.1.1 (p. 256) to read its
 * transactions from a file. Pass the name of the file as an argument to main
 * (§ 6.2.5, p. 218).
 */

#ifndef CHAPTER_08_EXERCISE_06_H_
#define CHAPTER_08_EXERCISE_06_H_

#include <iostream>  // std::istream, std::ostream
#include <string>    // std::string

struct Sales_data {
  std::string book_nombre;
  uint16_t units_sold = 0;
  double revenue = 0.0F;

  /**
   * @brief Reads transaction data from input stream
   * @param istream Input stream
   * @return Reference to the input stream
   */
  std::istream& Input(std::istream& istream) {
    double price;
    istream >> book_nombre >> units_sold >> price;
    revenue = units_sold * price;
    return istream;
  }

  /**
   * @brief Calculates average price
   * @return Average price or 0 if no sales
   */
  float AvgPrice() const {
    if (units_sold) {
      return revenue / units_sold;
    } else {
      return 0.F;
    }
  }

  /**
   * @brief Outputs sales data to stream
   * @param out Output stream
   * @return Reference to the output stream
   */
  std::ostream& Dump(std::ostream& ostream) {
    ostream << book_nombre << ' '  //
            << units_sold << ' '   //
            << revenue << ' '      //
            << AvgPrice();

    return ostream;
  }

  /**
   * @brief Combines another Sales_data into this object
   * @param rhs Right-hand side Sales_data
   * @return Reference to this object
   */
  Sales_data& Combine(const Sales_data& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
  }
};

#endif  // CHAPTER_08_EXERCISE_06_H_
