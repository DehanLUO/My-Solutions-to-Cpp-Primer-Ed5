/*
 * Exercise 14.2: Write declarations for the overloaded input, output, addition,
 * and compound-assignment operators for Sales_data.
 */

#ifndef CHAPTER_14_EXERCISE_02_H_
#define CHAPTER_14_EXERCISE_02_H_

#include <cstdint>   // uint16_t
#include <iostream>  // std::istream, std::ostream
#include <string>    // std::string

class Sales_data {
  // friend declarations
  friend std::ostream& operator<<(std::ostream&, const Sales_data&);
  friend std::istream& operator>>(std::istream&, Sales_data&);

  friend Sales_data operator+(const Sales_data&, const Sales_data&);

 private:
  std::string book_nombre_;  // International Standard Book Number
  uint16_t units_sold_;      // Quantity sold
  float revenue_;            // Gross income from sales

 public:
  /**
   * @brief Default constructor
   */
  Sales_data() : Sales_data("", 0, 0.F) {};

  /**
   * @brief Constructs with ISBN only
   * @param book_nombre International Standard Book Number
   * @note Explicit to prevent implicit conversions
   */
  explicit Sales_data(const std::string& book_nombre)
      : Sales_data(book_nombre, 0, 0.F) {}

  /**
   * @brief Complete manual initialization
   * @param book_nombre International Standard Book Number
   * @param units_sold Quantity of units sold
   * @param revenue Total sales revenue
   * @note Explicit to prevent implicit conversions
   */
  explicit Sales_data(const std::string& book_nombre, uint16_t units_sold,
                      float revenue)
      : book_nombre_(book_nombre), units_sold_(units_sold), revenue_(revenue) {}

  /**
   * @brief Copy constructor
   * @param other Source object to copy from
   */
  Sales_data(const Sales_data& others)
      : book_nombre_(others.book_nombre_),
        units_sold_(others.units_sold_),
        revenue_(others.revenue_) {}

  /**
   * @brief Stream initialization constructor
   * @param input_stream Input stream to read from
   * @note Explicit to prevent implicit conversions
   */
  explicit Sales_data(std::istream& input_stream) { input_stream >> *this; }

  /**
   * @brief Retrieves the ISBN identifier
   * @return Constant reference to the ISBN string
   */
  const std::string& isbn() const { return book_nombre_; }

  /**
   * @brief Compound addition assignment operator
   * @param rhs Sales_data to add
   * @return Reference to modified object
   * @note Only combines if ISBNs match
   * Time Complexity O(1)
   * Space Complexity O(1)
   */
  Sales_data& operator+=(const Sales_data& rhs) {
    // Verify ISBNs match
    if (book_nombre_ != rhs.book_nombre_)
      throw std::logic_error("Cannot add Sales_data with different ISBNs");

    revenue_ += rhs.revenue_;
    units_sold_ += rhs.units_sold_;
    return *this;
  }

  /**
   * @brief Calculates average selling price per unit
   * @return Mean price or 0 if no units sold
   */
  /* inline */ float avg_price()
      const {  // Since the funcion is defined inside the class body, the
               // compiler automatically treats it as `inline`
    /*
     * Price calculation implementation:
     * 1. Guards against division by zero
     * 2. Uses explicit static_cast for type safety
     * 3. Returns 0.0F for empty transactions
     */
    if (0 == units_sold_) {
      return 0.F;
    }

    return revenue_ / static_cast<float>(units_sold_);  // narrow int -> float
  }
};

/**
 * @brief Overloaded input operator for Sales_data
 * @param istream Input stream
 * @param item Sales_data object to populate
 * @return Reference to the input stream
 * @note Reads data in format: ISBN units_sold unit_price
 * Time Complexity O(1)
 * Space Complexity O(1)
 */
inline std::istream& operator>>(std::istream& istream, Sales_data& item) {
  float unit_price;
  // Attempt to read all three fields
  if (istream >> item.book_nombre_ >> item.units_sold_ >> unit_price) {
    // Calculate total revenue if read succeeds
    item.revenue_ = static_cast<float>(item.units_sold_) * unit_price;
  } else {
    // Reset to default state if read fails
    item = Sales_data();
  }

  return istream;
}

/**
 * @brief Overloaded output operator for Sales_data
 * @param ostream Output stream
 * @param item Sales_data object to output
 * @return Reference to the output stream
 * @note Output format: ISBN units_sold revenue avg_price
 * Time Complexity O(1)
 * Space Complexity O(1)
 */
inline std::ostream& operator<<(std::ostream& ostream, const Sales_data& item) {
  return ostream << item.book_nombre_ << ' '  //
                 << item.units_sold_ << ' '   //
                 << item.revenue_ << ' '      //
                 << item.avg_price();
}

/**
 * @brief Overloaded addition operator for Sales_data
 * @param lhs Left-hand side operand
 * @param rhs Right-hand side operand
 * @return New Sales_data object representing combined sales
 * @note Only combines if ISBNs match
 * Time Complexity O(1)
 * Space Complexity O(1)
 */
inline Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
  Sales_data sum = lhs;  // Use copy constructor
  sum += rhs;            // Use compound assignment
  return sum;
}

#endif  // CHAPTER_14_EXERCISE_02_H_
