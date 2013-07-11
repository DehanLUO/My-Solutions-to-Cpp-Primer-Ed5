/*
 * Exercise 15.30: Write your own version of the Basket class and use it to
 * compute prices for the same transactions as you used in the previous
 * exercises.
 */

#ifndef CHAPTER_15_EXERCISE_30_QUOTE_H_
#define CHAPTER_15_EXERCISE_30_QUOTE_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string
#include <utility>   // std::move

/**
 * @class Quote
 * @brief Base class representing a generic quotable item with basic pricing
 * @note Serves as the foundation for specialized quote types with custom
 * pricing logic
 */
class Quote {
 public:
  /**
   * @brief Default constructor
   */
  Quote() = default;

  /**
   * @brief Parameterized constructor
   * @param book ISBN identifier for the quoted item
   * @param sales_price Base price per unit before discounts
   */
  Quote(const std::string& book, double sales_price)
      : book_nombre_(book), price_(sales_price) {}

  /**
   * @brief Copy constructor
   * @param other Quote object to copy from
   */
  Quote(const Quote& other)
      : book_nombre_(other.book_nombre_), price_(other.price_) {}

  /**
   * @brief Move constructor
   * @param other Quote object to move from
   */
  Quote(Quote&& other) noexcept
      : book_nombre_(std::move(other.book_nombre_)), price_(other.price_) {}

  /**
   * @brief Copy assignment operator
   * @param other Quote object to copy from
   * @return Reference to this object
   */
  Quote& operator=(const Quote& other) {
    if (&other == this) return *this;

    book_nombre_ = other.book_nombre_;
    price_ = other.price_;
    return *this;
  }

  /**
   * @brief Move assignment operator
   * @param other Quote object to move from
   * @return Reference to this object
   */
  Quote& operator=(Quote&& other) noexcept {
    if (&other == this) return *this;

    book_nombre_ = std::move(other.book_nombre_);
    price_ = other.price_;
    return *this;
  }

  /**
   * @brief Virtual destructor for proper polymorphic cleanup
   * @note Essential for derived class object destruction through base
   * pointers
   */
  virtual ~Quote() = default;

  /**
   * @brief Retrieve ISBN identifier
   * @return Constant reference to the ISBN string
   */
  std::string ISBN() const { return book_nombre_; }

  /**
   * @brief Calculate net price for specified quantity
   * @param quantity Number of units to price
   * @return Total price after applying appropriate pricing logic
   * @note Virtual function allowing derived classes to override with custom
   *       pricing
   * @time_complexity O(1) - Constant time operation
   * @space_complexity O(1) - No additional space required
   */
  virtual double NetPrice(std::size_t quantity) const {
    return quantity * price_;
  }

  /**
   * @brief Clone function for polymorphic copying (lvalue overload)
   * @return Pointer to a new Quote object with the same state as *this
   * @note Called when copying from an lvalue (preserves the current object)
   */
  virtual Quote* Clone() const& { return new Quote(*this); }

  /**
   * @brief Clone function for polymorphic copying (rvalue overload)
   * @return Pointer to a new Quote object constructed via move semantics
   * @note Called when cloning from an rvalue (may optimize performance by
   *       moving resources)
   */
  virtual Quote* Clone() && { return new Quote(std::move(*this)); }

 private:
  std::string book_nombre_;  // ISBN identifier
 protected:
  double price_ = 0.0;  // Base price per unit
};

/**
 * @brief Calculate and display total price for quoted item
 * @param ostream Output stream for result display
 * @param item Reference to Quote object (base or derived)
 * @param quantity Number of units being purchased
 * @return Total price calculated for the transaction
 * @note Demonstrates runtime polymorphism through virtual function call
 * @time_complexity O(1) - Constant time operation
 * @space_complexity O(1) - No additional space required
 */
double print_total(std::ostream& ostream, const Quote& item,
                   std::size_t quantity) {
  double total_price = item.NetPrice(quantity);
  ostream << "ISBN: " << item.ISBN()      //
          << " | Quantity: " << quantity  //
          << " | Total due: " << total_price << '\n';

  return total_price;
}

#endif  // CHAPTER_15_EXERCISE_30_QUOTE_H_
