/*
 * Exercise 13.2: Explain why the following declaration is illegal:
 *     Sales_data::Sales_data(Sales_data rhs);
 */

#ifndef CHAPTER_13_EXERCISE_02_H_
#define CHAPTER_13_EXERCISE_02_H_

#include <iostream>
#include <string>

class Sales_data {
 public:
  /*
   * ILLEGAL COPY CONSTRUCTOR DECLARATION:
   * Problem: Parameter should be const reference
   * Wrong: will cause compilation error
   *
   * The call would never succeed---to call the copy constructor, we would need
   * to use the copy constructor to copy the argument, but to copy the argument,
   * we would need to call the copy constructor, and so on indefinitely.
   */
  // Sales_data(Sales_data rhs)
  //     : book_no_(rhs.book_no_),
  //       units_sold_(rhs.units_sold_),
  //       revenue_(rhs.revenue_) {
  //   std::cout << "Copying Sales_data (but this will never work)\n";
  // }

  // CORRECT VERSION:
  Sales_data(const Sales_data& rhs)
      : book_no_(rhs.book_no_),
        units_sold_(rhs.units_sold_),
        revenue_(rhs.revenue_) {
    std::cout << "Copying Sales_data (but this will never work)\n";
  }

 private:
  std::string book_no_;
  unsigned units_sold_ = 0;
  double revenue_ = 0.0;
};

#endif  // CHAPTER_13_EXERCISE_02_H_
