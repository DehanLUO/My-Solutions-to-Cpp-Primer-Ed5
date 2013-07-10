/*
 * Exercise 15.15: Define your own versions of Disc_quote and Bulk_quote.
 */

#ifndef CHAPTER_15_EXERCISE_15_BULKQUOTE_H_
#define CHAPTER_15_EXERCISE_15_BULKQUOTE_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string

#include "exercise-15-discquote.h"  // DiscQuote

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
   * @brief Calculate net price with bulk discount logic
   * @param quantity Number of units to price
   * @return Total price with bulk discount applied if eligible
   * @note Applies discount to all units when quantity >= min_quantity
   */
  double NetPrice(std::size_t quantity) const override {
    if (quantity >= min_quantity_) return quantity * price_ * (1 - discount_);

    return quantity * price_;
  }
};

#endif  // CHAPTER_15_EXERCISE_15_BULKQUOTE_H_
