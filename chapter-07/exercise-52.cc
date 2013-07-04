/*
 * Exercise 7.52: Using our first version of Sales_data from § 2.6.1 (p. 72),
 * explain the following initialization. Identify and fix any problems.
 *     Sales_data item = {"978-0590353403", 25, 15.99};
 */

#include <string>  // std::string

/**
 * @brief Original Sales_data aggregate structure
 */
// struct Sales_data {
//   std::string bookNo;
//   unsigned units_sold = 0;
//   double revenue = 0.0;
// };

/**
 * @brief Corrected Sales_data aggregate structure
 * Removed in-class initializers to qualify as aggregate
 */
struct Sales_data {
  std::string bookNo;   // No in-class initializer
  unsigned units_sold;  // Removed = 0
  double revenue;       // Removed = 0.0
};

int main() {
  /*
   * Now valid aggregate initialization:
   * 1. No user-provided constructors
   * 2. No private/protected members
   * 3. No in-class initializers
   * 4. No base classes/virtual functions
   */
  Sales_data item = {"978-0590353403", 25, 15.99};

  return 0;
}
