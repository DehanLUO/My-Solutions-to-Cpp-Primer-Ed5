/*
 * Exercise 7.37: Using the version of Sales_data from this section, determine
 * which constructor is used to initialize each of the following variables and
 * list the values of the data members in each object:
 *     Sales_data first_item(cin);
 *     int main() {
 *       Sales_data next;
 *       Sales_data last("9-999-99999-9");
 *     }
 */

#include <iostream>  // std::istream, std::cout
#include <string>    // std::string

// The version of Sales_data from this section
class Sales_data {
  friend std::istream &read(std::istream &, Sales_data &);

 private:
  std::string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;

 public:
  // defines the default constructor as well as one that takes a string argument
  Sales_data(std::string s = "") : bookNo(s) {}
  // remaining constructors unchanged
  Sales_data(std::string s, unsigned cnt, double rev)
      : bookNo(s), units_sold(cnt), revenue(rev * cnt) {}
  Sales_data(std::istream &is) { read(is, *this); }
};

std::istream &read(std::istream &is, Sales_data &) { return is; }

int main() {
  /*
   * first_item construction:
   * - Uses istream constructor (most specialized match)
   * - Members set by read() operation during construction
   */
  Sales_data first_item(std::cin);

  /*
   * next construction:
   * - Uses default constructor (as well as one that takes a string argument)
   * - All members get their in-class initializers:
   *   bookNo="", units_sold=0, revenue=0.0
   */
  Sales_data next;

  /*
   * last construction:
   * - Uses string constructor (exact match for const char*)
   * - bookNo initialized, others get default values
   */
  Sales_data last("9-999-99999-9");
  return 0;
}
