/*
 * Exercise 15.5: Define your own version of the Bulk_quote class.
 */

#ifndef CHAPTER_15_EXERCISE_05_BULKQUOTE_H_
#define CHAPTER_15_EXERCISE_05_BULKQUOTE_H_

#include <cstddef>  // std::size_t

#include "exercise-03-quote.h"  // Quote

/**
 * @class BulkQuote
 * @brief Derived class implementing bulk quantity discount pricing
 * @note Applies percentage discount when purchase quantity meets minimum
 *       threshold
 */
class BulkQuote : public Quote {  // BulkQuote inherits from Quote
 public:
  /**
   * @brief Default constructor
   */
  BulkQuote() = default;

  /**
   * @brief Parameterized constructor with bulk discount parameters
   * @param book ISBN identifier
   * @param sales_price Base price per unit
   * @param min_quantity Minimum quantity required for discount eligibility
   * @param discount Fractional discount rate (e.g., 0.15 for 15% discount)
   * @note Discount applied only when quantity >= min_quantity
   */
  BulkQuote(const std::string& book, double sales_price,
            std::size_t min_quantity, double discount)
      : Quote(book, sales_price),
        min_quantity_(min_quantity),
        discount_(ValidateDiscount(discount)) {}

  /**
   * @brief Get minimum quantity required for discount
   * @return Minimum quantity threshold
   */
  std::size_t GetMinQuantity() const { return min_quantity_; }

  /**
   * @brief Get current discount rate
   * @return Fractional discount rate
   */
  double GetDiscount() const { return discount_; }

  /**
   * @brief Set new discount rate with validation
   * @param new_discount Fractional discount rate
   * @note Ensures discount remains within valid range [0.0, 1.0]
   */
  void SetDiscount(double new_discount) {
    discount_ = ValidateDiscount(new_discount);
  }

  /**
   * @brief Override NetPrice to implement bulk discount logic
   * @param quantity Number of units to price
   * @return Total price with bulk discount applied if eligible
   * @note Applies discount only when quantity meets or exceeds minimum
   *       threshold
   * @time_complexity O(1) - Constant time comparison and arithmetic
   * @space_complexity O(1) - No additional space required
   */
  double NetPrice(std::size_t quantity) const override {
    if (quantity >= min_quantity_) return quantity * (1 - discount_) * price_;
    return quantity * price_;
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

  std::size_t min_quantity_ = 0;  // minimum purchase for discount to apply
  double discount_ = 0.0;         // fractional discount to apply
};

#endif  // CHAPTER_15_EXERCISE_05_BULKQUOTE_H_
