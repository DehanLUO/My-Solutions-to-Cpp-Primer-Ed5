/*
 * Exercise 14.11: What, if anything, is wrong with the following Sales_data
 * input operator? What would happen if we gave this operator the data in the
 * previous exercise?
 *     istream& operator>>(istream& in, Sales_data& s) {
 *       double price;
 *       in >> s.bookNo >> s.units_sold >> price;
 *       s.revenue = s.units_sold * price;
 *       return in;
 *     }
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-14/exercise-11.cc && ./main

 */
