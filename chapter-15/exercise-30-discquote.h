/*
 * Exercise 15.30: Write your own version of the Basket class and use it to
 * compute prices for the same transactions as you used in the previous
 * exercises.
 */

#ifndef CHAPTER_15_EXERCISE_30_DISCQUOTE_H_
#define CHAPTER_15_EXERCISE_30_DISCQUOTE_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string

#include "exercise-30-quote.h"  // Quote

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
   * @brief Copy constructor
   * @param other DiscQuote object to copy from
   */
  DiscQuote(const DiscQuote& other)
      : Quote(other),
        min_quantity_(other.min_quantity_),
        discount_(other.discount_) {}

  /**
   * @brief Move constructor
   * @param other DiscQuote object to move from
   */
  DiscQuote(DiscQuote&& other) noexcept
      : Quote(std::move(other)),
        min_quantity_(other.min_quantity_),
        discount_(other.discount_) {}

  /**
   * @brief Copy assignment operator
   * @param other DiscQuote object to copy from
   * @return Reference to this object
   */
  DiscQuote& operator=(const DiscQuote& other) {
    if (&other == this) return *this;

    Quote::operator=(other);
    min_quantity_ = other.min_quantity_;
    discount_ = other.discount_;

    return *this;
  }

  /**
   * @brief Move assignment operator
   * @param other DiscQuote object to move from
   * @return Reference to this object
   */
  DiscQuote& operator=(DiscQuote&& other) noexcept {
    if (&other == this) return *this;

    Quote::operator=(std::move(other));
    min_quantity_ = other.min_quantity_;
    discount_ = other.discount_;

    return *this;
  }

  /**
   * @brief Virtual destructor for proper cleanup
   */
  virtual ~DiscQuote() = default;

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
  virtual double NetPrice(std::size_t quantity) const override = 0;

  /**
   * @brief Clone function for polymorphic copying (lvalue overload)
   * @return Pointer to a new DiscQuote object with the same state as *this
   * @note Called when copying from an lvalue (preserves the current object)
   */
  virtual DiscQuote* Clone() const& override = 0;

  /**
   * @brief Clone function for polymorphic copying (rvalue overload)
   * @return Pointer to a new DiscQuote object constructed via move semantics
   * @note Called when cloning from an rvalue (may optimize performance by
   *       moving resources)
   */
  virtual DiscQuote* Clone() && override = 0;

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

#endif  // CHAPTER_15_EXERCISE_30_DISCQUOTE_H_
