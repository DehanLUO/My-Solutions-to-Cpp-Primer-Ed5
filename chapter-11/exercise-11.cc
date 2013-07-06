/*
 * Exercise 11.11: Redefine bookstore without using decltype.
 */

#include <set>  // std::mutiset

#include "../chapter-07/exercise-26.h"  // Sales_data

// Comparison function for Sales_data objects
bool CompareIsbn(const Sales_data &lhs, const Sales_data &rhs) {
  return lhs.isbn() < rhs.isbn();
}

int main() {
  {
    // Option 1: Using function pointer type directly
    std::multiset<Sales_data, bool (*)(const Sales_data &, const Sales_data &)>
        bookstore(CompareIsbn);
  }

  {
    // Option 2: Using type alias
    using SalesDataComparator =
        bool (*)(const Sales_data &, const Sales_data &);
    std::multiset<Sales_data, SalesDataComparator> bookstore(CompareIsbn);
  }

  {
    // Option 3: Using typedef alias
    typedef bool (*SalesDataComparator)(const Sales_data &, const Sales_data &);
    std::multiset<Sales_data, SalesDataComparator> bookstore(CompareIsbn);
  }

  {
    // Option 4: Using function object
    struct CompareIsbnFunctor {
      bool operator()(const Sales_data &lhs, const Sales_data &rhs) {
        return lhs.isbn() < rhs.isbn();
      }
    };
    std::multiset<Sales_data, CompareIsbnFunctor> bookstore;
  }

  return 0;
}
