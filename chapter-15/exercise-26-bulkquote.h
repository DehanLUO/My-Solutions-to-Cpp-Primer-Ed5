/*
 * Exercise 15.26: Define the Quote and Bulk_quote copy-control members to do
 * the same job as the synthesized versions. Give them and the other
 * constructors print statements that identify which function is running. Write
 * programs using these classes and predict what objects will be created and
 * destroyed. Compare your predictions with the output and continue
 * experimenting until your predictions are reliably correct.
 */

#ifndef CHAPTER_15_EXERCISE_26_BULKQUOTE_H_
#define CHAPTER_15_EXERCISE_26_BULKQUOTE_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string

#include "exercise-26-discquote.h"  // DiscQuote

class BulkQuote : public DiscQuote {
 public:
  /**
   * @brief Default constructor
   */
  BulkQuote() { std::cout << "BulkQuote() called\n"; }

  /**
   * @brief Parameterized constructor with bulk discount parameters
   * @param book ISBN identifier
   * @param sales_price Base price per unit
   * @param min_quantity Minimum quantity for discount eligibility
   * @param discount Fractional discount rate
   */
  BulkQuote(const std::string& book, double sales_price,
            std::size_t min_quantity, double discount)
      : DiscQuote(book, sales_price, min_quantity, discount) {
    std::cout << "BulkQuote("                      //
              << "const std::string& " << book     //
              << ", double " << sales_price        //
              << ", std::size_t " << min_quantity  //
              << ", double " << discount << ") called\n";
  }

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

#endif  // CHAPTER_15_EXERCISE_26_BULKQUOTE_H_
