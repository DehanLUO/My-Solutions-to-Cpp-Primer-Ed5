/*
 * Exercise 15.6: Test your print_total function from the exercises in § 15.2.1
 * (p. 595) by passing both Quote and Bulk_quote objects o that function.
 */

#include <iostream>  // std::cout

#include "exercise-03-quote.h"      // print_total
#include "exercise-05-bulkquote.h"  // BulkQuote

int main() {
  // Create BulkQuote with 10+ units required for 15% discount
  BulkQuote bulk_quote("978-0-13-470319-8", 100.00, 10, 0.15);

  std::cout << "Bulk discount pricing (15% off for 10+ units):\n";
  print_total(std::cout, bulk_quote, 5);   // Below threshold - no discount
  print_total(std::cout, bulk_quote, 10);  // At threshold - discount applied
  print_total(std::cout, bulk_quote, 25);  // Above threshold - discount applied

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-06.cc && ./main
 * Bulk discount pricing (15% off for 10+ units):
 * ISBN: 978-0-13-470319-8 | Quantity: 5 | Total due: 500
 * ISBN: 978-0-13-470319-8 | Quantity: 10 | Total due: 850
 * ISBN: 978-0-13-470319-8 | Quantity: 25 | Total due: 2125
 */
