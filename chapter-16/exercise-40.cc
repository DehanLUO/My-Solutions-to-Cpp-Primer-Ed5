/*
 * Exercise 16.40: Is the following function legal? If not, why not? If it is
 * legal, what, if any, are the restrictions on the argument type(s) that can be
 * passed, and what is the return type?
 *     template <typename It>
 *     auto fcn3(It beg, It end) -> decltype(*beg + 0) {
 *       // process the range
 *       return *beg;  // return a copy of an element from the range
 *     }
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-16/exercise-40.cc && ./main

 */
