/*
 * Exercise 14.10: Describe the behavior of the Sales_data input operator if
 * given the following input:
 * (a) 0-201-99999-9 10 24.95   (b) 10 24.95 0-210-99999-9
 */

#include <iostream>  // std::cin, std::cout

#include "exercise-09.h"  // Sales_data

int main() {
  Sales_data item;
  std::cin >> item;
  std::cout << item;
}

/*
 * (a) 0-201-99999-9 10 24.95
 * 1. Successful parsing of all three fields:
 *    - ISBN: "0-201-99999-9" (string)
 *    - Units Sold: 10 (unsigned)
 *    - Unit Price: 24.95 (float)
 * 2. Correct revenue calculation:
 *    - 10 units * $24.95 = $249.50
 * 3. Output matches expected format:
 *    - ISBN Units_Sold Revenue Avg_Price
 *    - "0-201-99999-9 10 249.5 24.95"
 */

/*
 * (b) 10 24.95 0-210-99999-9
 * 1. Step-by-step parsing behavior:
 *    - ISBN: "10" (string)
 *    - Units Sold: 24 (unsigned; only the integer part of "24.95" is consumed)
 *    - Unit Price: 0.95 (float; the remaining ".95" is parsed here)
 * 2. Revenue calculation:
 *    - 24 units * $0.95 = $22.80
 * 3. Output result:
 *    - ISBN Units_Sold Revenue Avg_Price
 *    - "10 24 22.8 0.95"
 */

/*
 * $ g++ -o main chapter-14/exercise-10.cc && ./main
 * 0-201-99999-9 10 24.95
 * 0-201-99999-9 10 249.5 24.95
 * $ ./main
 * 10 24.95 0-210-99999-9
 * 10 24 22.8 0.95
 */
