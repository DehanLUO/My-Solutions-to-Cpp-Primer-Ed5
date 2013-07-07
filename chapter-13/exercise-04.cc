/*
 * Exercise 13.4: Assuming Point is a class type with a public copy constructor,
 * identify each use of the copy constructor in this program fragment:
 *     Point global;
 *     Point foo_bar(Point arg) {
 *       Point local = arg, *heap = new Point(global);
 *       *heap = local;
 *       Point pa[4] = {local, *heap};
 *       return *heap;
 *     }
 */

#include <iostream>  // std::cout

class Point {
 public:
  Point() { std::cout << "CONSTRUCT default @" << this << "\n"; }
  Point(const Point& other) { std::cout << "CONSTRUCT copy @" << this << "\n"; }
};

Point global;  // 1. Default constructor

Point foo_bar(Point arg) {  // 2. Copy constructor (pass by value)

  std::cout << "3. Copy constructor (direct initialization)\n"
            << "4. Copy constructor (new initialization)\n";
  Point local = arg,      // 3. Copy constructor (direct initialization
      *heap =             // Point assignment, not construct copy
      new Point(global);  // 4. new: Copy constructor (new initialization)

  *heap = local;  // Point assignment, not construct copy

  std::cout << "5. Copy constructor (array element 0)\n"
            << "6. Copy constructor (array element 1)\n"
            << "7. Default constructed (array element 2)\n"
            << "8. Default constructed (array element 3)\n";
  Point pa[4] = {
      local,  // 5. Copy constructor (array element 0)
      *heap,  // 6. Copy constructor (array element 1)
              // 7+8. Default constructed (array element 2,3)
  };

  std::cout << "9. Copy constructor (return by value)\n";
  return *heap;  // 9. Copy constructor (return by value)
}

int main() {
  foo_bar(global);

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-04.cc && ./main
 * CONSTRUCT default @0x102aae000
 * CONSTRUCT copy @0x7ff7bd453c5b
 * 3. Copy constructor (direct initialization)
 * 4. Copy constructor (new initialization)
 * CONSTRUCT copy @0x7ff7bd453c2f
 * CONSTRUCT copy @0x6000004ac050
 * 5. Copy constructor (array element 0)
 * 6. Copy constructor (array element 1)
 * 7. Default constructed (array element 2)
 * 8. Default constructed (array element 3)
 * CONSTRUCT copy @0x7ff7bd453c10
 * CONSTRUCT copy @0x7ff7bd453c11
 * CONSTRUCT default @0x7ff7bd453c12
 * CONSTRUCT default @0x7ff7bd453c13
 * 9. Copy constructor (return by value)
 * CONSTRUCT copy @0x7ff7bd453c5a
 */
