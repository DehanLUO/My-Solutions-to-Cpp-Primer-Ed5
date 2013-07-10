/*
 * Exercise 15.15: Define your own versions of Disc_quote and Bulk_quote.
 */

#ifndef CHAPTER_15_EXERCISE_15_QUOTE_H_
#define CHAPTER_15_EXERCISE_15_QUOTE_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string

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
   * @brief Virtual destructor for proper polymorphic cleanup
   * @note Essential for derived class object destruction through base pointers
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

#endif  // CHAPTER_15_EXERCISE_15_QUOTE_H_
