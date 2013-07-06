/*
 * Exercise 11.19: Define a variable that you initialize by calling begin() on
 * the multiset named bookstore from § 11.2.2 (p. 425). Write the variable’s
 * type without using auto or decltype.
 */

#include <set>  // std::mutiset

#include "../chapter-07/exercise-26.h"  // Sales_data

// Comparison function for Sales_data objects
bool CompareIsbn(const Sales_data &lhs, const Sales_data &rhs) {
  return lhs.isbn() < rhs.isbn();
}

int main() {
  using Type = std::multiset<Sales_data,
                             bool (*)(const Sales_data &, const Sales_data &)>;

  // bookstore can have several transactions with the same ISBN
  // elements in bookstore will be in ISBN order
  Type bookstore(CompareIsbn);

  // Initialize iterator
  Type::iterator iter = bookstore.begin();

  return 0;
}
