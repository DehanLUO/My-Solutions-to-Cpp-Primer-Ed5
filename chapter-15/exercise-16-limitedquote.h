/*
 * Exercise 15.16: Rewrite the class representing a limited discount strategy,
 * which you wrote for the exercises in § 15.2.2 (p. 601), to inherit from
 * Disc_quote.
 */

#ifndef CHAPTER_15_EXERCISE_16_LIMITEDQUOTE_H_

#endif  // CHAPTER_15_EXERCISE_16_LIMITEDQUOTE_H_

#include <algorithm>  // std::min

#include "exercise-15-discquote.h"  // DiscQuote

class LimitedQuote : public DiscQuote {
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
      : DiscQuote(book, sales_price, max_discounted,
                  ValidateDiscount(discount)) {}

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
    const std::size_t discounted_units = std::min(quantity, GetMinQuantity());

    // Calculate number of units at regular price
    const std::size_t regular_units = quantity - discounted_units;

    // Apply discount to eligible units, regular price to remainder
    return (discounted_units * price_ * (1 - GetDiscount())) +
           (regular_units * price_);
  }

 private:
  /**
   * @brief Validate discount rate to ensure reasonable values
   * @param discount Proposed discount rate
   * @return Validated discount rate clamped to [0.0, 0.95] range
   * @note Prevents unrealistic discount rates while allowing business
   * flexibility
   */
  double ValidateDiscount(double discount) const override {
    if (discount < 0.0) return 0.0;
    if (discount > 0.95) return 0.95;  // Cap at 95% to prevent negative prices
    return discount;
  }
};

#define CHAPTER_15_EXERCISE_16_LIMITEDQUOTE_H_
