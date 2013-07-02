/*
 * Exercise 2.42: Write your own version of the Sales_data.h header and use it
 * to rewrite the exercise from § 2.6.2 (p. 76)
 */

#include <iostream>  // std::cout

#include "exercise-40.h"  // Sales_data

int ExerciseC1E20() {
  Sales_data book;

  std::cout << "Enter sales data: \n";
  while (book.Input()) {
    std::cout << "isbn units_sold revenue avg_price: ";
    book.Dump();
  }

  return 0;
}

int ExerciseC1E21() {
  Sales_data sales_data_a;
  Sales_data sales_data_b;

  std::cout << "Enter two sales records with the same ISBN:\n";
  sales_data_a.Input();
  sales_data_b.Input();
  if (sales_data_a.book_nombre == sales_data_b.book_nombre) {
    sales_data_a.units_sold += sales_data_b.units_sold;
    sales_data_a.revenue += sales_data_b.revenue;
    std::cout << "Summary: ISBN, quantity sold, total sales revenue, and "
                 "average selling price:\n";
    sales_data_a.Dump();
  } else {
    std::cerr << "ISBNs do not match\n";
    return -1;
  }

  return 0;
}

int ExerciseC1E22() {
  Sales_data total;
  Sales_data sales_data;

  std::cout << "Enter some sales records with the same ISBN:\n";
  if (!total.Input()) {
    std::cerr << "Invalid data!\n";
    return -1;
  }

  while (sales_data.Input()) {
    if (sales_data.book_nombre == total.book_nombre) {  // same ISBN
      total.units_sold += sales_data.units_sold;
      total.revenue += sales_data.revenue;
    } else {  // different ISBN
      std::cerr << "ISBNs do not match\n";
      return -1;
    }
  }

  std::cout << "Summary: ISBN, quantity sold, total sales revenue, and "
               "average selling price:\n";
  total.Dump();

  return 0;
}

int ExerciseC1E23AndC1E24() {
  Sales_data sales_base;  // Holds the current ISBN group to compare against

  std::cout << "Enter some sales records:\n";
  // Read first record as the base case
  if (sales_base.Input()) {
    Sales_data current_sales_record;  // Reads each incoming transaction
    int count = 1;  // Tracks number of records in current ISBN group

    // Process subsequent records
    while (current_sales_record.Input()) {
      if (sales_base.book_nombre == current_sales_record.book_nombre) {
        ++count;  // Increment if same ISBN as base
      } else {
        // Output stats for previous ISBN group
        std::cout << sales_base.book_nombre << " has " << count
                  << " sales records\n";
        sales_base = current_sales_record;  // Start new ISBN group
        count = 1;                          // Reset counter
      }
    }
    // Output the last ISBN group
    std::cout << sales_base.book_nombre << " has " << count
              << " sales records\n";
  } else {
    std::cerr << "No sales records\n";  // Handle empty input case
    return -1;
  }
  return 0;
}

int ExerciseC1E25() {
  Sales_data total;  // variable to hold data for the next transaction
  // read the first transaction and ensure that there are data to process
  if (total.Input()) {
    Sales_data trans;  // variable to hold the running sum;

    // read and process the remaining transactions
    while (trans.Input()) {
      // if we are still processing the same book
      if (total.book_nombre == trans.book_nombre) {
        // update the running total
        total.units_sold += trans.units_sold;
        total.revenue += trans.revenue;
      } else {
        // print results for the previous book
        total.Dump();
        total = trans;  // total now refers to the next book
      }
    }
    total.Dump();  // print the last transaction
  } else {
    // no input! warn the user
    std::cerr << "No data?!" << std::endl;
    return -1;  // indicate failure
  }
  return 0;
}

int main() {
  ExerciseC1E20();

  ExerciseC1E21();

  ExerciseC1E22();

  ExerciseC1E23AndC1E24();

  ExerciseC1E25();

  return 0;
}