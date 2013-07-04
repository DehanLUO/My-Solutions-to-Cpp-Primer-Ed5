/*
 * Exercise 7.6: Define your own versions of the add, read, and print functions.
 */

#ifndef CHAPTER_07_EXERCISE_06_H_
#define CHAPTER_07_EXERCISE_06_H_

#include <cstdint>  // uint16_t
#include <istream>  // std::istream
#include <ostream>  // std::ostream
#include <string>   // std::string

struct Sales_data {
  std::string book_nombre;  // International Standard Book Number
  uint16_t units_sold;      // Quantity sold
  float revenue;            // Gross income from sales

  /**
   * @brief Initializes all data members to default values
   */
  Sales_data();

  Sales_data(const Sales_data& target);

  /**
   * @brief Reads transaction data from input stream
   * @param input_stream Source of transaction data
   * @return Reference to the input stream after reading the data
   */
  std::istream& read(std::istream& input_stream);

  /**
   * @brief Outputs sales data to specified stream
   * @param output_stream Destination for formatted output
   * @return Reference to the output stream after writing the data
   */
  std::ostream& print(std::ostream& output_stream) const;

  /**
   * @brief Retrieves the ISBN identifier
   * @return Constant reference to the ISBN string
   */
  const std::string& isbn() const;

  /**
   * @brief Combines another Sales_data into current object
   * @param rhs Right-hand side Sales_data to combine
   * @return Reference to the modified current object
   */
  Sales_data& combine(const Sales_data& target);

  /**
   * @brief Adds two Sales_data objects
   * @param lhs Left operand for addition
   * @param rhs Right operand for addition
   * @return New Sales_data containing combined values
   */
  static Sales_data add(const Sales_data& lhs, const Sales_data& rhs);

  /**
   * @brief Resets all member variables to initial state
   */
  void initialize();

  /**
   * @brief Calculates average selling price per unit
   * @return Mean price or 0 if no units sold
   */
  float avg_price() const;
};

Sales_data::Sales_data() {
  /*
   * Constructor implementation using initialization delegation
   * Ensures consistent object state upon creation
   */
  initialize();
}

Sales_data::Sales_data(const Sales_data& target)
    : book_nombre(target.book_nombre),
      units_sold(target.units_sold),
      revenue(target.revenue) {}

void Sales_data::initialize() {
  /*
   * Member function implementation notes:
   * 1. Explicit state clearing prevents partial updates
   * 2. Floating-point literal suffix ensures type safety
   */
  book_nombre.clear();
  units_sold = 0;
  revenue = 0.0F;
}

std::istream& Sales_data::read(std::istream& input_stream) {
  /*
   * Input operation implementation details:
   * 1. Extracts book identifier, units sold, and unit price from the stream.
   * 2. Computes revenue as units_sold multiplied by unit_price.
   * 3. Ensures the object remains in a valid state after initialization.
   */
  float unit_price;
  input_stream >> book_nombre >> units_sold >> unit_price;
  revenue = static_cast<float>(units_sold) * unit_price;
  return input_stream;
}

std::ostream& Sales_data::print(std::ostream& output_stream) const {
  /*
   * Output formatting considerations:
   * 1. Space-separated fields for machine readability
   * 2. Avoids manual whitespace management via chaining
   * 3. Delegates price calculation to member function
   */
  output_stream << book_nombre << ' '  //
                << units_sold << ' '   //
                << revenue << ' '      //
                << avg_price() << '\n';

  return output_stream;
}

const std::string& Sales_data::isbn() const { return book_nombre; }

Sales_data& Sales_data::combine(const Sales_data& rhs) {
  /*
   * Combine operation implementation:
   * 1. Validates ISBN match before combining
   * 2. Performs member-wise addition
   * 3. Returns the reference to the current object
   */
  if (book_nombre != rhs.book_nombre) {
    return *this;
  }

  revenue += rhs.revenue;
  units_sold += rhs.units_sold;
  return *this;
}

/*
 * Static addition function:
 * 1. Creates copy of left operand
 * 2. Uses Combine for actual addition
 * 3. Returns new combined object
 */
Sales_data Sales_data::add(const Sales_data& lhs, const Sales_data& rhs) {
  Sales_data result = lhs;
  result.combine(rhs);

  return result;
}

float Sales_data::avg_price() const {
  /*
   * Price calculation implementation:
   * 1. Guards against division by zero
   * 2. Uses explicit static_cast for type safety
   * 3. Returns 0.0F for empty transactions
   */
  if (0 == units_sold) {
    return 0.F;
  }

  return revenue / static_cast<float>(units_sold);  // narrow int -> float
}

#endif  //  CHAPTER_07_EXERCISE_06_H_
