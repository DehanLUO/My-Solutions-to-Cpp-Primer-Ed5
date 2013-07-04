/*
 * Exercise 7.11: Add constructors to your Sales_data class and write a program
 * to use each of the constructors.
 */

#include <cstdint>   // uint16_t
#include <iostream>  // std::istream, std::ostream, std::cin, std::cout
#include <string>    // std::string

struct Sales_data {
  std::string book_nombre;  // International Standard Book Number
  uint16_t units_sold;      // Quantity sold
  float revenue;            // Gross income from sales

  /*
   * Constructor suite providing complete initialization options:
   * 1. Default construction
   * 2. ISBN-only initialization
   * 3. Complete manual initialization
   * 4. Stream-based initialization
   * 5. Copy construction
   */

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
      : book_nombre(book_nombre), units_sold(units_sold), revenue(revenue) {}

  /**
   * @brief Copy constructor
   * @param other Source object to copy from
   */
  Sales_data(const Sales_data& others) { *this = others; }

  /**
   * @brief Stream initialization constructor
   * @param input_stream Input stream to read from
   * @note Explicit to prevent implicit conversions
   */
  explicit Sales_data(std::istream& input_stream) { read(input_stream); }

  /**
   * @brief Reads transaction data from input stream
   * @param input_stream Source of transaction data
   * @return True if read succeeded, false otherwise
   */
  bool read(std::istream& input_stream) {
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

    *this = Sales_data();
    return false;
  }

  /**
   * @brief Outputs sales data to specified stream
   * @param output_stream Destination for formatted output
   */
  void print(std::ostream& output_stream) const {
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

  /**
   * @brief Retrieves the ISBN identifier
   * @return Constant reference to the ISBN string
   */
  const std::string& isbn() const { return book_nombre; }

  /**
   * @brief Combines another Sales_data into current object
   * @param rhs Right-hand side Sales_data to combine
   * @return True if combination succeeded, false if ISBNs mismatch
   */
  bool combine(const Sales_data& rhs) {
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

  /**
   * @brief Adds two Sales_data objects
   * @param lhs Left operand for addition
   * @param rhs Right operand for addition
   * @return New Sales_data containing combined values
   */
  static Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data result = lhs;
    result.combine(rhs);

    return result;
  }

  /**
   * @brief Calculates average selling price per unit
   * @return Mean price or 0 if no units sold
   */
  float avg_price() const {
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
};

int main() {
  // Collection demonstration
  std::vector<Sales_data> inventory = {
      Sales_data(),                     // 1. Default construction
      Sales_data("978-0-321-71411-4"),  // 2. ISBN-only construction
      Sales_data("978-0-321-71411-4", 25,
                 299.75),    // 3. Complete manual construction
      Sales_data(std::cin),  // 4. Stream initialization
  };

  for (const auto& item : inventory) {
    item.print(std::cout);
  }

  return 0;
}

/* $  g++ -o main chapter-07/exercise-11.cc  && ./main < data/book_sales
 *  0 0 0
 * 978-0-321-71411-4 0 0 0
 * 978-0-321-71411-4 25 299.75 11.99
 * 0-201-70353-X 4 99.96 24.99
 */
