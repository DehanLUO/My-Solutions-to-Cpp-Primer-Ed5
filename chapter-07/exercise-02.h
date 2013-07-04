/*
 * Exercise 7.2: Add the combine and isbn members to the Sales_data class you
 * wrote for the exercises in § 2.6.2 (p. 76).
 */

/*
 * § 7.1.1 Designing the Sales_data Class
 * Ultimately, we want Sales_data to support the same set of operations as the
 * Sales_item class. The Sales_item class had one **member function** (§ 1.5.2,
 * p.23), name isbn, and supported the +, =, +=, <<, and >> operators.
 * We will learn how to define our own operators in Chapter 14. For now, we will
 * define ordinary (named) functions for these operations. For reasons that we
 * will explain in § 14.1 (p.555), the functions that do addition and IO will
 * not be members of Sales_data. Instead, we will define those functions as
 * ordinary functions. The function that handles compund assignment will be a
 * member, and for reasons we will explain in § 7.1.5 (p.267), our class does
 * not need to define assignment.
 * Thus, the interface to Sales_data consists of the following operations:
 * - An isbn member function to return the object's ISBN
 * - A combine member function to add one Sales_data object into another
 * - A function named add to add two Sales_data objects
 * - A read function to read data from an istream into a Sales_data object
 * - A print function to print the value of a Sales_data object on an ostream
 */

#ifndef CHAPTER_07_EXERCISE_02_H_
#define CHAPTER_07_EXERCISE_02_H_

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
   * @return True if read succeeded, false otherwise
   */
  bool read(std::istream& input_stream);

  /**
   * @brief Outputs sales data to specified stream
   * @param output_stream Destination for formatted output
   */
  void print(std::ostream& output_stream) const;

  /**
   * @brief Retrieves the ISBN identifier
   * @return Constant reference to the ISBN string
   */
  const std::string& isbn() const;

  /**
   * @brief Combines another Sales_data into current object
   * @param rhs Right-hand side Sales_data to combine
   * @return True if combination succeeded, false if ISBNs mismatch
   */
  bool combine(const Sales_data& rhs);

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

bool Sales_data::read(std::istream& input_stream) {
  /*
   * Input operation implementation details:
   * 1. Uses chained extraction for transactional data
   * 2. Calculates derived revenue field
   * 3. Maintains object validity through initialization
   */
  float unit_price;
  if (input_stream >> book_nombre >> units_sold >> unit_price) {
    revenue = static_cast<float>(units_sold) * unit_price;
    return true;
  }

  initialize();
  return false;
}

void Sales_data::print(std::ostream& output_stream) const {
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
}

const std::string& Sales_data::isbn() const { return book_nombre; }

bool Sales_data::combine(const Sales_data& rhs) {
  /*
   * Combine operation implementation:
   * 1. Validates ISBN match before combining
   * 2. Performs member-wise addition
   * 3. Returns success status
   */
  if (book_nombre != rhs.book_nombre) {
    return false;
  }

  revenue += rhs.revenue;
  units_sold += rhs.units_sold;
  return true;
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

#endif  //  CHAPTER_07_EXERCISE_02_H_
