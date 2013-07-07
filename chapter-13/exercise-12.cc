/*
 * Exercise 13.12: How many destructor calls occur in the following code
 * fragment?
 *     bool fcn(const Sales_data *trans, Sales_data accum) {
 *       Sales_data item1(*trans), item2(accum);
 *       return item1.isbn() != item2.isbn();
 *     }
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-13/exercise-12.cc && ./main

 */
