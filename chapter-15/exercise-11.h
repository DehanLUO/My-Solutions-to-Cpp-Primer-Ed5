/*
 * Exercise 15.11: Add a virtual debug function to your Quote class hierarchy
 * that displays the data members of the respective classes.
 */

#ifndef CHAPTER_15_EXERCISE_11_QUOTE_H_
#define CHAPTER_15_EXERCISE_11_QUOTE_H_

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

  /**
   * @brief Debug function to display object state
   * @param ostream Output stream for display
   */
  virtual void Debug(std::ostream& ostream = std::cout) const {
    ostream << "Quote[ISBN: " << book_nombre_ << ", price: " << price_ << "]";
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

/**
 * @class BulkQuote
 * @brief Derived class implementing bulk quantity discount pricing
 * @note Applies percentage discount when purchase quantity meets minimum
 *       threshold
 */
class BulkQuote : public Quote {  // BulkQuote inherits from Quote
 public:
  /**
   * @brief Default constructor
   */
  BulkQuote() = default;

  /**
   * @brief Parameterized constructor with bulk discount parameters
   * @param book ISBN identifier
   * @param sales_price Base price per unit
   * @param min_quantity Minimum quantity required for discount eligibility
   * @param discount Fractional discount rate (e.g., 0.15 for 15% discount)
   * @note Discount applied only when quantity >= min_quantity
   */
  BulkQuote(const std::string& book, double sales_price,
            std::size_t min_quantity, double discount)
      : Quote(book, sales_price),
        min_quantity_(min_quantity),
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
   * @note Ensures discount remains within valid range [0.0, 1.0]
   */
  void SetDiscount(double new_discount) {
    discount_ = ValidateDiscount(new_discount);
  }

  /**
   * @brief Override NetPrice to implement bulk discount logic
   * @param quantity Number of units to price
   * @return Total price with bulk discount applied if eligible
   * @note Applies discount only when quantity meets or exceeds minimum
   *       threshold
   * @time_complexity O(1) - Constant time comparison and arithmetic
   * @space_complexity O(1) - No additional space required
   */
  double NetPrice(std::size_t quantity) const override {
    if (quantity >= min_quantity_) return quantity * (1 - discount_) * price_;
    return quantity * price_;
  }

  /**
   * @brief Debug function to display object state
   * @param ostream Output stream for display
   */
  void Debug(std::ostream& ostream = std::cout) const override {
    ostream << "BulkQuote[ISBN: " << ISBN() << ", price: " << price_
            << ", MinQty: " << min_quantity_
            << ", Discount: " << (discount_ * 100) << "%]";
  }

 private:
  /**
   * @brief Validate discount rate to ensure reasonable values
   * @param discount Proposed discount rate
   * @return Validated discount rate clamped to [0.0, 0.95] range
   * @note Prevents unrealistic discount rates while allowing business
   * flexibility
   */
  static double ValidateDiscount(double discount) {
    if (discount < 0.0) return 0.0;
    if (discount > 0.95) return 0.95;  // Cap at 95% to prevent negative prices
    return discount;
  }

  std::size_t min_quantity_ = 0;  // minimum purchase for discount to apply
  double discount_ = 0.0;         // fractional discount to apply
};

#endif  // CHAPTER_15_EXERCISE_11_QUOTE_H_
