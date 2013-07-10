/*
 * Exercise 15.15: Define your own versions of Disc_quote and Bulk_quote.
 */

#ifndef CHAPTER_15_EXERCISE_15_DISCQUOTE_H_
#define CHAPTER_15_EXERCISE_15_DISCQUOTE_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string

#include "exercise-15-quote.h"  // Quote

/**
 * @class DiscQuote
 * @brief Abstract base class for discount-based pricing strategies
 * @note Defines interface for quantity-based discount quotes
 */
class DiscQuote : public Quote {
 public:
  /**
   * @brief Default constructor
   */
  DiscQuote() = default;

  /**
   * @brief Virtual destructor for proper cleanup
   */
  virtual ~DiscQuote() = default;

  /**
   * @brief Parameterized constructor with discount parameters
   * @param book ISBN identifier
   * @param sales_price Base price per unit
   * @param min_quantity Minimum quantity for discount eligibility
   * @param discount Fractional discount rate (0.0 to 1.0)
   */
  DiscQuote(const std::string& book, double sales_price, std::size_t quantity,
            double discount)
      : Quote(book, sales_price),
        min_quantity_(quantity),
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
   * @throws std::invalid_argument if discount is outside valid range
   */
  void SetDiscount(double new_discount) {
    discount_ = ValidateDiscount(new_discount);
  }

  /**
   * @brief Pure virtual function for discount price calculation
   * @param quantity Number of units to price
   * @return Total price after applying discount strategy
   * @note Must be implemented by concrete derived classes
   */
  virtual double NetPrice(std::size_t quantity) const = 0;

 protected:
  /**
   * @brief Validate discount rate to ensure reasonable values
   * @param discount Proposed discount rate
   * @return Validated discount rate clamped to [0.0, 1.0] range
   * @note Prevents unrealistic discount rates while allowing business
   *       flexibility
   */
  virtual double ValidateDiscount(double discount) const {
    if (discount <= 0.0) {
      return 0.0;
    }

    if (discount >= 1.0) {
      return 1.0;
    }

    return discount;
  }

  std::size_t min_quantity_ = 0;  // Minimum quantity for discount eligibility
  double discount_ = 0.0;         // Fractional discount rate (0.0 to 1.0)
};

#endif  // CHAPTER_15_EXERCISE_15_DISCQUOTE_H_
