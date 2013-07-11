/*
 * Exercise 15.23: Assuming class D1 on page 620 had intended to override its
 * inherited fcn function, how would you fix that class? Assuming you fixed the
 * class so that fcn matched the definition in Base, how would the calls in that
 * section be resolved?
 */

#include <iostream>  // std::cout

class Base {
 public:
  virtual int fcn() {
    std::cout << "Base::fcn() called\n";
    return 0;
  }
};

class D1 : public Base {
 public:
  // hides fcn in the base; this fcn is not virtual
  // D1 inherits the definition of Base::fcn()
  int fcn() override {  // parameter list differs from fcn in Base
    std::cout << "D1::fcn() called\n";
    return 0;
  }

  virtual void f2() {  // new virtual function that does not exist in Base
    std::cout << "D1::f2() called\n";
  }
};

class D2 : public D1 {
 public:
  int fcn(int a) {  // nonvirtual function hides D1::fcn(int)
    std::cout << "D2::fcn(int) called: " << a << "\n";
    return a;
  }

  int fcn() {  // overrides virtual fcn from Base
    std::cout << "D2::fcn() called\n";
    return 0;
  }

  void f2() {  // overrides virtual f2 from D1
    std::cout << "D2::f2() called\n";
  }
};

int main() {
  Base bobj;
  D1 d1obj;
  D2 d2obj;

  Base *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
  bp1->fcn();  // virtual call, will call Base::fcn at run time
  bp2->fcn();  // virtual call, will call Base::fcn at run time
  bp3->fcn();  // virtual call, will call D2::fcn at run time

  D1 *d1p = &d1obj;
  D2 *d2p = &d2obj;
  // bp2->f2();  // error: Base has no member named f2
  d1p->f2();  // virtual call, will call D1::f2() at run time
  d2p->f2();  // virtual call, will call D2::f2() at run time

  Base *p1 = &d2obj;
  D1 *p2 = &d2obj;
  D2 *p3 = &d2obj;
  // p1->fcn(42);  // error: Base has no version of fcn that takes an int
  // p2->fcn(42);  // error: D1 has no version of fcn that takes an int
  p3->fcn(42);  // statically bound, calls D2::fcn(int)

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-23.cc && ./main
 * Base::fcn() called
 * D1::fcn() called
 * D2::fcn() called
 * D1::f2() called
 * D2::f2() called
 * D2::fcn(int) called: 42
 */
