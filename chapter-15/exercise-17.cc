/*
 * Exercise 15.17: Try to define an object of type Disc_quote and see what
 * errors you get from the compiler.
 */

#include "exercise-15-discquote.h"  // DiscQuote

int main() {
  DiscQuote disc_quote;

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-17.cc && ./main
 * chapter-15/exercise-17.cc:9:13: error: variable type 'DiscQuote' is an abstract class
 *     9 |   DiscQuote disc_quote;
 *       |             ^
 * chapter-15/exercise-15-discquote.h:71:18: note: unimplemented pure virtual method 'NetPrice' in 'DiscQuote'
 *    71 |   virtual double NetPrice(std::size_t quantity) const = 0;
 *       |                  ^
 * 1 error generated.
 */
