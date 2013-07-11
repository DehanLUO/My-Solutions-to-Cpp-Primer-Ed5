/*
 * Exercise 15.30: Write your own version of the Basket class and use it to
 * compute prices for the same transactions as you used in the previous
 * exercises.
 */

#ifndef CHAPTER_15_EXERCISE_30_BULKQUOTE_H_
#define CHAPTER_15_EXERCISE_30_BULKQUOTE_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string

#include "exercise-30-discquote.h"  // DiscQuote

class BulkQuote : public DiscQuote {
 public:
  /**
   * @brief Default constructor
   */
  BulkQuote() = default;

  /**
   * @brief Parameterized constructor with bulk discount parameters
   * @param book ISBN identifier
   * @param sales_price Base price per unit
   * @param min_quantity Minimum quantity for discount eligibility
   * @param discount Fractional discount rate
   */
  BulkQuote(const std::string& book, double sales_price,
            std::size_t min_quantity, double discount)
      : DiscQuote(book, sales_price, min_quantity, discount) {}

  /**
   * @brief Copy constructor
   * @param other BulkQuote object to copy from
   */
  BulkQuote(const BulkQuote& other) : DiscQuote(other) {}

  /**
   * @brief Move constructor
   * @param other BulkQuote object to move from
   */
  BulkQuote(BulkQuote&& other) noexcept : DiscQuote(std::move(other)) {}

  /**
   * @brief Copy assignment operator
   * @param other BulkQuote object to copy from
   * @return Reference to this object
   */
  BulkQuote& operator=(const BulkQuote& other) {
    if (&other == this) return *this;

    DiscQuote::operator=(other);

    return *this;
  }

  /**
   * @brief Move assignment operator
   * @param other BulkQuote object to move from
   * @return Reference to this object
   */
  BulkQuote& operator=(BulkQuote&& other) noexcept {
    if (&other == this) return *this;

    DiscQuote::operator=(std::move(other));

    return *this;
  }

  /**
   * @brief Destructor
   */
  ~BulkQuote() = default;

  /**
   * @brief Calculate net price with bulk discount logic
   * @param quantity Number of units to price
   * @return Total price with bulk discount applied if eligible
   * @note Applies discount to all units when quantity >= min_quantity
   */
  double NetPrice(std::size_t quantity) const override {
    if (quantity >= min_quantity_) return quantity * price_ * (1 - discount_);

    return quantity * price_;
  }

  /**
   * @brief Clone function for polymorphic copying (lvalue overload)
   * @return Pointer to a new BulkQuote object with the same state as *this
   * @note Called when copying from an lvalue (preserves the current object)
   */
  BulkQuote* Clone() const& override { return new BulkQuote(*this); }

  /**
   * @brief Clone function for polymorphic copying (rvalue overload)
   * @return Pointer to a new BulkQuote object constructed via move semantics
   * @note Called when cloning from an rvalue (may optimize performance by
   *       moving resources)
   */
  BulkQuote* Clone() && override { return new BulkQuote(std::move(*this)); }
};

#endif  // CHAPTER_15_EXERCISE_30_BULKQUOTE_H_
