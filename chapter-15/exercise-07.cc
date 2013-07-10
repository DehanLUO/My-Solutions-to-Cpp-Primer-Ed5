/*
 * Exercise 15.7: Define a class that implements a limited discount strategy,
 * which applies a discount to books purchased up to a given limit. If the
 * number of copies exceeds that limit, the normal price applies to those
 * purchased beyond the limit.
 */

#include <iostream>  // std::cout

#include "exercise-03-quote.h"  // Quote, print_total

/**
 * @class LimitedQuote
 * @brief Derived class implementing limited quantity discount pricing
 * @note Applies discount only to first N units, regular price for additional
 * units beyond the specified limit
 */
class LimitedQuote : public Quote {
 public:
  /**
   * @brief Default constructor
   */
  LimitedQuote() = default;

  /**
   * @brief Parameterized constructor with limited discount parameters
   * @param book ISBN identifier
   * @param sales_price Base price per unit
   * @param max_discounted Maximum number of units eligible for discount
   * @param discount Fractional discount rate (e.g., 0.20 for 20% discount)
   * @note Discount applied only to first max_discounted units
   */
  LimitedQuote(const std::string& book, double sales_price,
               std::size_t max_discounted, double discount)
      : Quote(book, sales_price),
        max_discounted_units_(max_discounted),
        discount_rate_(ValidateDiscount(discount)) {}

  /**
   * @brief Override NetPrice to implement limited quantity discount logic
   * @param quantity Number of units to price
   * @return Total price with limited discount applied
   * @note Applies discount only to first max_discounted_units_ units,
   *       regular price for any additional units
   * @time_complexity O(1) - Constant time arithmetic operations
   * @space_complexity O(1) - No additional space required
   */
  double NetPrice(std::size_t quantity) const override {
    // Calculate number of units eligible for discount
    const std::size_t discounted_units =
        std::min(quantity, max_discounted_units_);

    // Calculate number of units at regular price
    const std::size_t regular_units = quantity - discounted_units;

    // Apply discount to eligible units, regular price to remainder
    return (discounted_units * price_ * (1 - discount_rate_)) +
           (regular_units * price_);
  }

  /**
   * @brief Get maximum number of discounted units
   * @return Maximum discounted units limit
   */
  std::size_t GetMaxDiscountedUnits() const { return max_discounted_units_; }

  /**
   * @brief Get current discount rate
   * @return Fractional discount rate
   */
  double GetDiscountRate() const { return discount_rate_; }

  /**
   * @brief Set new discount rate with validation
   * @param new_discount Fractional discount rate
   */
  void SetDiscountRate(double new_discount) {
    discount_rate_ = ValidateDiscount(new_discount);
  }

  /**
   * @brief Set new maximum discounted units limit
   * @param new_max New maximum units limit
   */
  void SetMaxDiscountedUnits(std::size_t new_max) {
    max_discounted_units_ = new_max;
  }

  /**
   * @brief Calculate effective price per unit for given quantity
   * @param quantity Number of units
   * @return Average price per unit after discounts
   * @note Useful for comparing different pricing strategies
   */
  double EffectiveUnitPrice(std::size_t quantity) const {
    if (quantity == 0) return 0.0;
    return NetPrice(quantity) / quantity;
  }

 private:
  /**
   * @brief Validate discount rate to ensure reasonable values
   * @param discount Proposed discount rate
   * @return Validated discount rate clamped to [0.0, 0.95] range
   * @note Prevents unrealistic discount rates while allowing business
   * flexibility
   */
  static double ValidateDiscount(double discount) {
    if (discount < 0.0) return 0.0;
    if (discount > 0.95) return 0.95;  // Cap at 95% to prevent negative prices
    return discount;
  }

  std::size_t max_discounted_units_ = 0;
  double discount_rate_ = 0.0;
};

int main() {
  // Create LimitedQuote with discount for first 5 units only (20% discount)
  LimitedQuote limited_quote("978-0-13-679491-9", 100.00, 5, 0.20);

  // Test various quantity scenarios
  std::cout << "Limited discount pricing (20% off for first 5 units only):\n";

  print_total(std::cout, limited_quote, 3);  // All units discounted
  print_total(std::cout, limited_quote, 5);  // All units discounted
  print_total(std::cout, limited_quote,
              8);  // First 5 discounted, remaining 3 regular
  print_total(std::cout, limited_quote,
              10);  // First 5 discounted, remaining 5 regular
  print_total(std::cout, limited_quote,
              15);  // First 5 discounted, remaining 10 regular
  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-07.cc && ./main
 * Limited discount pricing (20% off for first 5 units only):
 * ISBN: 978-0-13-679491-9 | Quantity: 3 | Total due: 240
 * ISBN: 978-0-13-679491-9 | Quantity: 5 | Total due: 400
 * ISBN: 978-0-13-679491-9 | Quantity: 8 | Total due: 700
 * ISBN: 978-0-13-679491-9 | Quantity: 10 | Total due: 900
 * ISBN: 978-0-13-679491-9 | Quantity: 15 | Total due: 1400
 */
