/*
 * Exercise 15.14: Given the classes from the previous exercise and the
 * following objects, determine which function is called at run time:
 *     base bobj;    base *bp1 = &bobj;     base &br1 = bobj;
 *     derived dobj; base *bp2 = &dobj;     base &br2 = dobj;
 *     (a) bobj.print();   (b) dobj.print();   (c) bp1->name();
 *     (d) bp2->name();    (e) br1.print();    (f) br2.print();
 */

#include <iostream>  // std::cout

#include "exercise-13.h"  // base, derived

int main() {
  // Create objects for analysis
  base bobj;
  derived dobj;

  // Various references and pointers
  base* bp1 = &bobj;  // Base pointer to Base object
  base& br1 = bobj;   // Base reference to Base object
  base* bp2 = &dobj;  // Base pointer to Derived object
  base& br2 = dobj;   // Base reference to Derived object

  /*
   * (a) bobj.Print():
   *    Static type: Base, Dynamic type: Base
   *    Result: base::print(): base
   *    REASON: Base object calls Base::Print
   */
  bobj.print(std::cout);  // (a) Base::Print()
  std::cout << '\n';

  /*
   * (b) dobj.Print():
   *    Static type: Derived, Dynamic type: Derived
   *    REASON: Derived object calls Derived::Print
   */
  dobj.print(std::cout);  // (b) Derived::Print()
  std::cout << '\n';

  /*
   * (c) bp1->Name():
   *    Static type: Base*, Dynamic type: Base*
   *    REASON: Non-virtual function, uses static type (Base*)
   */
  bp1->name();  // (c) Base::Name()

  /*
   * (d) bp2->Name():
   *    Static type: Base*, Dynamic type: Derived*
   *    REASON: Non-virtual function, uses static type (Base*)
   */
  bp2->name();  // (d) Base::Name()

  /*
   * (e) br1.Print():
   *    Static type: Base&, Dynamic type: Base&
   *    REASON: Virtual function, but dynamic type is Base
   */
  br1.print(std::cout);  // (e) Base::Print()
  std::cout << '\n';

  /*
   * (f) br2.Print():
   *    Static type: Base&, Dynamic type: Derived&
   *    REASON: Virtual function, dynamic type is Derived
   */
  br2.print(std::cout);  // (f) Derived::Print()
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-14.cc && ./main
 * base::print(): base
 * base::print(): base | derived::print(): 42
 * base::name() called
 * base::name() called
 * base::print(): base
 * base::print(): base | derived::print(): 42
 */
