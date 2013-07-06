/*
 * Exercise 10.32: Rewrite the bookstore problem from § 1.6 (p. 24) using a
 * vector to hold the transactions and various algorithms to do the processing.
 * Use sort with your compareIsbn function from § 10.3.1 (p. 387) to arrange the
 * transactions in order, and then use find and accumulate to do the sum.
 */

#include <algorithm>  // std::sort, std::find_if
#include <iostream>   // std::cin, std::cout, std::cerr
#include <iterator>   // std::istream_iterator
#include <numeric>    // std::accumulate
#include <vector>     // std::vector

#include "../include/Sales_item.h"  // Sales_item

/**
 * @brief Compare two Sales_items by ISBN
 * @param item1 First Sales_item
 * @param item2 Second Sales_item
 * @return True if item1's ISBN is less than item2's
 */
bool CompareIsbn(const Sales_item& item1, const Sales_item& item2) {
  return item1.isbn() < item2.isbn();
}

int main() {
  // Read all transactions into a vector
  std::vector<Sales_item> items;
  std::copy(std::istream_iterator<Sales_item>(std::cin),
            std::istream_iterator<Sales_item>(), std::back_inserter(items));

  if (items.empty()) {
    std::cerr << "No data?!" << '\n';
    return -1;
  }

  // Sort transactions by ISBN
  std::sort(items.begin(), items.end(), CompareIsbn);

  // Process each book group
  auto current = items.begin();
  while (current != items.end()) {
    // Find first item with different ISBN
    auto next =
        std::find_if(current, items.end(), [&current](const Sales_item& item) {
          return item.isbn() != current->isbn();
        });

    // Sum all transactions for current ISBN
    Sales_item total = std::accumulate(current + 1, next, *current);

    std::cout << total << '\n';
    current = next;
  }

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-32.cc && ./main < data/book_sales
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-78345-X 5 110 22
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 16 198 12.375
 * 0-399-82477-1 5 226.95 45.39
 */
