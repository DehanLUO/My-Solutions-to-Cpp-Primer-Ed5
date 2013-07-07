/*
 * Exercise 13.16: What if the parameter in f were const numbered&? Does that
 * change the output? If so, why? What output gets generated?
 */

#include <cstdint>   // uint16_t
#include <iostream>  // std::cout

class numbered {
  friend void f(const numbered&);  // Now takes a reference

 public:
  // Each new object gets a unique serial number via next_id++;
  numbered() : mysn(next_id++) {}

  numbered(const numbered& other) : mysn(next_id++) {}

 private:
  static uint16_t next_id;
  uint16_t mysn;
};

uint16_t numbered::next_id = 0;

void f(const numbered& s) { std::cout << s.mysn << '\n'; }

int main() {
  /*
   * a: Default constructor -> a.mysn = 0 (next_id -> 1)
   * b = a: Copy constructor -> b.mysn = 1 (next_id -> 2)
   * c = b: Copy constructor -> c.mysn = 2 (next_id -> 3)
   */
  numbered a, b = a, c = b;

  f(a);  // Pass by reference -> no copy -> prints a.mysn (0)
  f(b);  // Pass by reference -> no copy -> prints b.mysn (1)
  f(c);  // Pass by reference -> no copy -> prints c.mysn (2)

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-16.cc && ./main
 * 0
 * 1
 * 2
 */
