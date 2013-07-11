/*
 * Exercise 15.30: Write your own version of the Basket class and use it to
 * compute prices for the same transactions as you used in the previous
 * exercises.
 */

#include <iostream>  // std::ostream, std::cout
#include <memory>    // std::shared_Ptr
#include <set>       // std::multiset

#include "exercise-30-bulkquote.h"
#include "exercise-30-quote.h"

class Basket {
 public:
  /**
   * @brief Add a copy of the given Quote (lvalue version).
   * @param sale The Quote object to be copied into the Basket.
   *
   * This function clones the given Quote (polymorphically)
   * and stores it in the Basket.
   */
  void AddItem(const Quote &sale) {
    items_.insert(std::shared_ptr<Quote>(sale.Clone()));
  }

  /**
   * @brief Add a Quote using move semantics (rvalue version).
   * @param sale The Quote object to be moved into the Basket.
   *
   * This overload is more efficient when the caller can provide
   * a temporary object (rvalue). It invokes the rvalue overload
   * of Clone() to transfer resources.
   */
  void AddItem(Quote &&sale) {
    items_.insert(std::shared_ptr<Quote>(std::move(sale).Clone()));
  }

  /**
   * @brief Calculate total price for all items in the basket
   * @return Total price including all discounts
   * @note Demonstrates polymorphic behavior through virtual function calls
   */
  double TotalReceipt(std::ostream &ostream) const {
    double sum = 0.0;

    // Iterate through multiset (ordered by ISBN)
    for (auto iter = items_.cbegin(); iter != items_.cend();) {
      // Find range of items with same ISBN
      auto upper = items_.upper_bound(*iter);

      // Calculate quantity of this ISBN
      std::size_t quantity = std::distance(iter, upper);

      // Calculate total price for this ISBN
      double item_total = (*iter)->NetPrice(quantity);
      sum += item_total;

      // Print item details
      ostream << "ISBN: " << (*iter)->ISBN() << '\n'  //
              << "  Quantity: " << quantity << '\n'   //
              << "  Total: " << item_total << '\n';

      // Advance iterator to the next group
      iter = upper;
    }

    ostream << "GRAND TOTAL: " << sum << '\n';
    return sum;
  }

 private:
  /**
   * @brief Comparator for ordering Quote objects by ISBN.
   * @param lhs Pointer to the left-hand side Quote.
   * @param rhs Pointer to the right-hand side Quote.
   * @return true if lhs ISBN is less than rhs ISBN.
   */
  static bool compare(const std::shared_ptr<Quote> &lhs,
                      const std::shared_ptr<Quote> &rhs) {
    return lhs->ISBN() < rhs->ISBN();
  }

  // Multiset of Quote objects (shared_ptr for polymorphism, ordered by ISBN).
  std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items_{compare};
};

int main() {
  Basket basket;

  // Add 12 copies of BulkQuote with ISBN "978-1234567890"
  for (int count = 0; count < 12; ++count)
    basket.AddItem(BulkQuote("978-1234567890", 50.0, 10, 0.1));

  // Add 6 copies of BulkQuote with ISBN "978-9876543210"
  for (int count = 0; count < 6; ++count)
    basket.AddItem(BulkQuote("978-9876543210", 30.0, 5, 0.15));

  // Add 10 copies of BulkQuote with ISBN "978-5555555555"
  for (int count = 0; count < 10; ++count)
    basket.AddItem(BulkQuote("978-5555555555", 25.0, 8, 0.2));

  // Print total receipt
  basket.TotalReceipt(std::cout);

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-30.cc && ./main
 * ISBN: 978-1234567890
 *   Quantity: 12
 *   Total: 540
 * ISBN: 978-5555555555
 *   Quantity: 10
 *   Total: 200
 * ISBN: 978-9876543210
 *   Quantity: 6
 *   Total: 153
 * GRAND TOTAL: 893
 */
