/*
 * Exercise 13.14: Assume that numbered is a class with a default constructor
 * that generates a unique serial number for each object, which is stored in a
 * data member named mysn. Assuming numbered uses the synthesized copy-control
 * members and given the following function:
 *     void f(numbered s) { cout << s.mysn << endl; }
 * what output does the following code produce?
 *     numbered a, b = a, c = b;
 *     f(a); f(b); f(c);
 */

/*
 * Synthesized copy constructor/assignment would copy mysn directly (not
 * generate new IDs)
 */

#include <cstdint>   // uint16_t
#include <iostream>  // std::cout

class numbered {
  friend void f(numbered);

 public:
  // Each new object gets a unique serial number via next_id++;
  numbered() : mysn(next_id++) {}

 private:
  static uint16_t next_id;
  uint16_t mysn;
};

uint16_t numbered::next_id = 0;

void f(numbered s) { std::cout << s.mysn << '\n'; }

int main() {
  numbered a, b = a, c = b;
  f(a);
  f(b);
  f(c);

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-14.cc && ./main
 * 0
 * 0
 * 0
 */
