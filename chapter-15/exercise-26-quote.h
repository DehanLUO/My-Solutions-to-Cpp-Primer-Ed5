/*
 * Exercise 15.26: Define the Quote and Bulk_quote copy-control members to do
 * the same job as the synthesized versions. Give them and the other
 * constructors print statements that identify which function is running. Write
 * programs using these classes and predict what objects will be created and
 * destroyed. Compare your predictions with the output and continue
 * experimenting until your predictions are reliably correct.
 */

#ifndef CHAPTER_15_EXERCISE_26_QUOTE_H_
#define CHAPTER_15_EXERCISE_26_QUOTE_H_

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
  Quote() { std::cout << "Quote() called\n"; }

  /**
   * @brief Parameterized constructor
   * @param book ISBN identifier for the quoted item
   * @param sales_price Base price per unit before discounts
   */
  Quote(const std::string& book, double sales_price)
      : book_nombre_(book), price_(sales_price) {
    std::cout << "Quote(const std::string& " << book  //
              << ", double " << sales_price << ") called\n";
  }

  /**
   * @brief Copy constructor
   * @param other Quote object to copy from
   */
  Quote(const Quote& other)
      : book_nombre_(other.book_nombre_), price_(other.price_) {
    std::cout << "Quote(const Quote& other) called\n";
  }

  /**
   * @brief Move constructor
   * @param other Quote object to move from
   */
  Quote(Quote&& other) noexcept
      : book_nombre_(std::move(other.book_nombre_)), price_(other.price_) {
    std::cout << "Quote(Quote&& other) called\n";
  }

  /**
   * @brief Copy assignment operator
   * @param other Quote object to copy from
   * @return Reference to this object
   */
  Quote& operator=(const Quote& other) {
    std::cout << "Quote& operator=(const Quote& other) called\n";

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
    std::cout << "Quote& operator=(Quote&& other) called\n";

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
  virtual ~Quote() { std::cout << "~Quote() called\n"; }

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

#endif  // CHAPTER_15_EXERCISE_26_QUOTE_H_
