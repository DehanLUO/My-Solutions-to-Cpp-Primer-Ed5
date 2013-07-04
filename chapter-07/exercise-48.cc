/*
 * Exercise 7.48: Assuming the Sales_data constructors are not explicit, what
 * operations happen during the following definitions
 *     string null_isbn("9-999-99999-9");
 *     Sales_data item1(null_isbn);
 *     Sales_data item2("9-999-99999-9");
 * What happens if the Sales_data constructors are explicit?
 */

#include <string>  // std::string

#include "exercise-47.h"  // Salesd_data

/*
 * 1. Direct initialization (Sales_data item(...)):
 *    - Always considers explicit constructors
 *    - Allows implicit conversions for arguments
 *
 * 2. Copy initialization (Sales_data item = ...):
 *    - Bypassed by explicit constructors
 *    - Requires implicit conversion sequence
 *
 * 3. Reference binding:
 *    - const std::string& can bind to temporaries (§11.6.3)
 */

int main() {
  std::string null_isbn("9-999-99999-9");

  /* Case 1: Direct initialization with string object */
  Sales_data item1(null_isbn);
  /*
   * Behavior (explicit or not):
   * 1. Exact match to Sales_data(const std::string&)
   * 2. No conversions required
   * 3. Always well-formed (§11.6.1)
   */

  /* Case 2: Direct initialization with string literal */
  Sales_data item2("9-999-99999-9");
/*
 * Non-explicit constructor:
 * 1. const char[12] → std::string (temporary)
 * 2. std::string → Sales_data
 *
 * Explicit constructor:
 * 1. Still valid direct initialization
 * 2. const char[12] → std::string allowed
 * 3. Explicit constructor can be used in direct-init (§12.3.1)
 */

/* Case 3: Copy initialization (contrast) */
#ifndef EXPLICIT_CTOR
  Sales_data item3 = "9-999-99999-9";  // Requires non-explicit
#endif

  return 0;
}

/* $ g++ -D EXPLICIT_CTOR -o main chapter-07/exercise-48.cc && ./main
 * Sales_data(const std::string& book_nombre=9-999-99999-9, uint16_t units_sold=0, revenue=0)
 * Sales_data(const std::string& book_nombre=9-999-99999-9)
 * Sales_data(const std::string& book_nombre=9-999-99999-9, uint16_t units_sold=0, revenue=0)
 * Sales_data(const std::string& book_nombre=9-999-99999-9)
 */
