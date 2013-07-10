/*
 * Exercise 15.10: Recalling the discussion from § 8.1 (p. 311), explain how the
 * program on page 317 that passed an ifstream to the Sales_data read function
 * works.
 */

/*
 * ifstream input(argv[1]);   // open the file of sales transactions
 * ofstream output(argv[2]);  // open the output file
 * Sales_data total;          // variable to hold the running sum
 * if (read(input, total)) {  // read the first transaction
 *   Sales_data trans;        // variable to hold data for the next transaction
 *   while (read(input, trans)) {         // read the remaining transactions
 *     if (total.isbn() == trans.isbn())  // check isbns
 *       total.combine(trans);            // update the running total
 *     else {
 *       print(output, total) << endl;  // print the results
 *       total = trans;                 // process the next book
 *     }
 *   }
 *   print(output, total) << endl;  // print the last transaction
 * } else                           // there was no input
 *   cerr << "No data?!" << endl;
 */

#include <fstream>   // std::ifstream
#include <iostream>  // std::istream

#include "../chapter-14/exercise-45.h"  // Sales_data

std::istream& read(std::istream& istream, Sales_data& item);

/*
 * C++ standard library stream classes form an inheritance hierarchy:
 *   istream (base class for input streams)
 *     ^
 *     |
 *   ifstream (derived class for file input streams)
 * This inheritance relationship enables polymorphic behavior where derived
 * stream objects can be used wherever base stream references are expected.
 */
