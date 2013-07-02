/*
 * Exercise 2.40: Write your own version of the Sales_data class.
 */

#ifndef CHAPTER_02_EXERCISE_40_H_
#define CHAPTER_02_EXERCISE_40_H_

#include <iostream>  // std::cin, std::cout
#include <string>    // std::string

struct Sales_data {
  std::string book_nombre;
  uint16_t units_sold = 0;
  float revenue = 0.0F;

  bool Input() {
    float price;
    if (std::cin >> book_nombre >> units_sold >> price) {
      revenue = units_sold * price;
      return true;
    }

    book_nombre.clear();
    units_sold = 0;
    revenue = 0.0F;
    return false;
  }

  float AvgPrice() const {
    if (units_sold) {
      return revenue / units_sold;
    } else {
      return 0.F;
    }
  }

  void Dump() {
    std::cout << book_nombre << ' '  //
              << units_sold << ' '   //
              << revenue << ' '      //
              << AvgPrice() << '\n';
  }
};

#endif  //  CHAPTER_02_EXERCISE_40_H_
