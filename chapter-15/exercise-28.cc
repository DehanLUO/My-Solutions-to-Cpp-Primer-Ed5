/*
 * Exercise 15.28: Define a vector to hold Quote objects but put Bulk_quote
 * objects into that vector. Compute the total net_price of all the elements in
 * the vector.
 */

#include <iostream>  // std::cout
#include <string>    // std::string
#include <vector>    // std::vector

#include "exercise-26-bulkquote.h"  // BulkQuote
#include "exercise-26-quote.h"      // Quote

int main() {
  std::vector<Quote> quote_vector;

  // Create BulkQuote objects
  BulkQuote bulk1("978-1234567890", 50.0, 10,
                  0.1);  // 10% discount for 10+ units
  BulkQuote bulk2("978-9876543210", 30.0, 5,
                  0.15);                            // 15% discount for 5+ units
  BulkQuote bulk3("978-5555555555", 25.0, 8, 0.2);  // 20% discount for 8+ units

  // Add BulkQuote objects to vector<Quote> - OBJECT SLICING OCCURS HERE
  std::cout << "Adding BulkQuote objects to vector<Quote>...\n";
  quote_vector.push_back(bulk1);
  quote_vector.push_back(bulk2);
  quote_vector.push_back(bulk3);

  // CALCULATING TOTAL NET PRICE

  std::size_t quantities[] = {12, 6, 10};  // Test quantities for each item
  double total_net_price = 0.0;

  for (std::size_t i = 0; i < quote_vector.size(); ++i) {
    double item_price = quote_vector[i].NetPrice(quantities[i]);
    total_net_price += item_price;

    std::cout << "Item " << i + 1 << " (ISBN: " << quote_vector[i].ISBN()
              << "):\n"                                   //
              << "  Quantity: " << quantities[i] << "\n"  //
              << "  Net Price: $" << item_price << "\n";
  }

  std::cout << "TOTAL NET PRICE: $" << total_net_price << "\n\n";

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-28.cc && ./main
 * Quote(const std::string& 978-1234567890, double 50) called
 * DiscQuote(const std::string& 978-1234567890, double 50, std::size_t 10, double 0.1) called
 * BulkQuote(const std::string& 978-1234567890, double 50, std::size_t 10, double 0.1) called
 * Quote(const std::string& 978-9876543210, double 30) called
 * DiscQuote(const std::string& 978-9876543210, double 30, std::size_t 5, double 0.15) called
 * BulkQuote(const std::string& 978-9876543210, double 30, std::size_t 5, double 0.15) called
 * Quote(const std::string& 978-5555555555, double 25) called
 * DiscQuote(const std::string& 978-5555555555, double 25, std::size_t 8, double 0.2) called
 * BulkQuote(const std::string& 978-5555555555, double 25, std::size_t 8, double 0.2) called
 * Adding BulkQuote objects to vector<Quote>...
 * Quote(const Quote& other) called
 * Quote(const Quote& other) called
 * Quote(Quote&& other) called
 * ~Quote() called
 * Quote(const Quote& other) called
 * Quote(Quote&& other) called
 * Quote(Quote&& other) called
 * ~Quote() called
 * ~Quote() called
 * Item 1 (ISBN: 978-1234567890):
 *   Quantity: 12
 *   Net Price: $600
 * Item 2 (ISBN: 978-9876543210):
 *   Quantity: 6
 *   Net Price: $180
 * Item 3 (ISBN: 978-5555555555):
 *   Quantity: 10
 *   Net Price: $250
 * TOTAL NET PRICE: $1030
 *
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * ~Quote() called
 * ~Quote() called
 */
