/*
 * Exercise 15.27: Redefine your Bulk_quote class to inherit its constructors.
 */

#ifndef CHAPTER_15_EXERCISE_27_BULKQUOTE_H_
#define CHAPTER_15_EXERCISE_27_BULKQUOTE_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string

#include "exercise-26-discquote.h"  // DiscQuote

/**
 * @class BulkQuote
 * @brief Concrete class implementing bulk quantity discount pricing
 * @note Inherits constructors from DiscQuote
 * inheritance
 */
class BulkQuote : public DiscQuote {
 public:
  /**
   * @brief Inherit all constructors from DiscQuote
   * @note Using declaration: using DiscQuote::DiscQuote;
   * This inherits:
   * - DiscQuote()
   * - DiscQuote(const std::string&, double, std::size_t, double)
   */
  using DiscQuote::DiscQuote;

  /**
   * @brief Copy constructor
   * @param other BulkQuote object to copy from
   */
  BulkQuote(const BulkQuote& other) : DiscQuote(other) {
    std::cout << "BulkQuote(const BulkQuote& other) called\n";
  }

  /**
   * @brief Move constructor
   * @param other BulkQuote object to move from
   */
  BulkQuote(BulkQuote&& other) noexcept : DiscQuote(std::move(other)) {
    std::cout << "BulkQuote(BulkQuote&& other) called\n";
  }

  /**
   * @brief Copy assignment operator
   * @param other BulkQuote object to copy from
   * @return Reference to this object
   */
  BulkQuote& operator=(const BulkQuote& other) {
    std::cout << "BulkQuote& operator=(const BulkQuote& other) called\n";

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
    std::cout << "BulkQuote& operator=(BulkQuote&& other) called\n";

    if (&other == this) return *this;

    DiscQuote::operator=(std::move(other));

    return *this;
  }

  /**
   * @brief Destructor
   */
  ~BulkQuote() { std::cout << "~BulkQuote() called\n"; }

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

#endif  // CHAPTER_15_EXERCISE_27_BULKQUOTE_H_
