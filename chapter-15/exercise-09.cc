/*
 * Exercise 15.9: When is it possible for an expression’s static type to differ
 * from its dynamic type? Give three examples in which the static and dynamic
 * type differ.
 */

#include "exercise-03-quote.h"      // Quote, print_total
#include "exercise-05-bulkquote.h"  // BulkQuote

int main() {
  /*
   * EXAMPLE 1: Function parameter accepting base reference
   * Static type: const Quote& (function parameter type)
   * Dynamic type: BulkQuote& (actual argument type)
   */
  BulkQuote bulk("978-BULK-123", 100.0, 10, 0.15);
  // PrintTotal expects const Quote& but receives BulkQuote
  // Virtual function call uses dynamic type (BulkQuote::NetPrice)
  print_total(std::cout, bulk, 3);  // Direct pass of derived object

  /*
   * EXAMPLE 2: Base pointer pointing to derived object
   * Static type: Quote* (pointer to base class)
   * Dynamic type: BulkQuote* (actual derived type)
   */
  Quote *ptr_quote = &bulk;
  print_total(std::cout, *ptr_quote, 15);  // Should apply bulk discount

  /*
   * EXAMPLE 3: Base reference referencing derived object
   * Static type: Quote& (reference to base class)
   * Dynamic type: BulkQuote& (actual derived type)
   */
  Quote &ref_quote = bulk;
  print_total(std::cout, ref_quote, 8);  // Should NOT apply discount

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-09.cc && ./main
 * ISBN: 978-BULK-123 | Quantity: 3 | Total due: 300
 * ISBN: 978-BULK-123 | Quantity: 15 | Total due: 1275
 * ISBN: 978-BULK-123 | Quantity: 8 | Total due: 800
 */
