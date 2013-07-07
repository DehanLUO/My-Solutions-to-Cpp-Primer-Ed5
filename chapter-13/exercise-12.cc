/*
 * Exercise 13.12: How many destructor calls occur in the following code
 * fragment?
 *     bool fcn(const Sales_data *trans, Sales_data accum) {
 *       Sales_data item1(*trans), item2(accum);
 *       return item1.isbn() != item2.isbn();
 *     }
 */

#include "../chapter-07/exercise-47.h"  // Sales_data

/*
 * 1. Function Entry:
 *    - accum is copy constructed from argument (1 constructor call)
 *    - No destructor calls yet
 * 2. Inside Function:
 *    - item1 is copy constructed from *trans (1 constructor call)
 *    - item2 is copy constructed from accum (1 constructor call)
 *    - No destructor calls yet
 * 3. Function Exit:
 *    - item2 is destroyed (1 destructor call)
 *    - item1 is destroyed (1 destructor call)
 *    - accum is destroyed (1 destructor call)
 *
 * Total Destructor Calls: 3
 */
bool fcn(const Sales_data *trans, Sales_data accum) {  // accum copy-constructed
  Sales_data item1(*trans), item2(accum);  // item1 and item2 copy-constructed
  return item1.isbn() != item2.isbn();
}  // item2, item1, accum destroyed (3 destructor calls)

int main() { return 0; }

/*
 * $ g++ -o main chapter-13/exercise-12.cc && ./main

 */
