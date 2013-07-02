/*
 * Exercise 2.16: Which, if any, of the following assignments are invalid? If
 * they are valid, explain what they do.
 *     int i = 0, &r1 = i; double d = 0, &r2 = d;
 *     (a) r2 = 3.14159;   (b) r2 = r1;
 *     (c) i = r2;         (d) r1 = d;
 */

#include <iostream>  // std::cout

int main() {
  int i = 0, &r1 = i;
  double d = 0, &r2 = d;
  std::cout << i << ' ' << r1 << '\n';
  std::cout << d << ' ' << r2 << '\n';

  r2 = 3.14159;  // Valid. Assigns 3.14159 to `d` throuth reference `r2`
  std::cout << d << ' ' << r2 << '\n';

  // Valid. `r1` is `int`, promoted to `double, then assigned to `d` via `r2`
  r2 = r1;
  std::cout << d << ' ' << r2 << '\n';

  i = r2;  // Valid. `r2` is `double`, converted to `int`, truncating the value
  std::cout << i << '\n';

  r1 = d;  // Valid. `d` is converted to `int`, then assigned to `i` via `r1`
  std::cout << i << ' ' << r1 << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise-16.cc && ./main
 * 0 0
 * 0 0
 * 3.14159 3.14159
 * 0 0
 * 0
 * 0 0
 */
