/*
 * Exercise 13.15: Assume numbered has a copy constructor that generates a new
 * serial number. Does that change the output of the calls in the previous
 * exercise? If so, why? What output gets generated?
 */

#include <cstdint>   // uint16_t
#include <iostream>  // std::cout

class numbered {
  friend void f(numbered);

 public:
  // Each new object gets a unique serial number via next_id++;
  numbered() : mysn(next_id++) {}

  numbered(const numbered& other) : mysn(next_id++) {}

 private:
  static uint16_t next_id;
  uint16_t mysn;
};

uint16_t numbered::next_id = 0;

void f(numbered s) { std::cout << s.mysn << '\n'; }

int main() {
  /*
   * a: Default constructor -> a.mysn = 0 (next_id -> 1)
   * b = a: Copy constructor -> b.mysn = 1 (next_id -> 2)
   * c = b: Copy constructor -> c.mysn = 2 (next_id -> 3)
   */
  numbered a, b = a, c = b;

  /*
   * f(a): Pass by value -> copy constructor -> s.mysn = 3 (next_id -> 4)
   * Prints 3
   */
  f(a);

  /*
   * f(b): Pass by value -> copy constructor -> s.mysn = 4 (next_id -> 5)
   * Prints 4
   */
  f(b);

  /*
   * f(c): Pass by value -> copy constructor -> s.mysn = 5 (next_id -> 6)
   * Prints 5
   */
  f(c);

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-15.cc && ./main
 * 3
 * 4
 * 5
 */
