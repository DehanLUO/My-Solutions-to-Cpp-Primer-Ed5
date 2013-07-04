/*
 * Exercise 7.35: Explain the following code, indicating which definition of
 * Type or initVal is used for each use of those names. Say how you would fix
 * any errors.
 *     typedef string Type;
 *     Type initVal();
 *     class Exercise {
 *      public:
 *       typedef double Type;
 *       Type setVal(Type);
 *       Type initVal();
 *      private:
 *       int val;
 *     };
 *     Type Exercise::setVal(Type parm) {
 *       val = parm + initVal();
 *       return val;
 *     }
 */

#include <string>  // std::string
using std::string;

// Global scope definitions
typedef string Type;  // ::Type is std::string
Type initVal();       // ::initVal() returns string

class Exercise {
 public:
  typedef double Type;  // Exercise::Type is double
  Type setVal(Type);    // Takes double, returns double
  Type initVal();       // Returns double

 private:
  int val;  // Member variable
};

// Problematic definition:
/*
Type Exercise::setVal(Type parm) {
    val = parm + initVal();
    return val;
}
*/

// Corrected definition:
Exercise::Type Exercise::setVal(Type parm) {
  val = static_cast<int>(parm + initVal());
  return val;
}

Exercise::Type Exercise::initVal() { return 0.0; }

/*
 * Name Resolution Analysis:
 *
 * 1. Return Type (First Type):
 *    - Originally used ::Type (string) - WRONG
 *    - Should use Exercise::Type (double) - CORRECTED
 *
 * 2. Parameter Type (Second Type):
 *    - Correctly uses Exercise::Type (double)
 *
 * 3. initVal() call:
 *    - Originally would call ::initVal() (returns string) - WRONG
 *    - Now correctly calls Exercise::initVal() (returns double)
 *
 * 4. val assignment:
 *    - Added static_cast<int> since val is int but expression yields double
 *
 * Key Fixes:
 * 1. Qualified return type with Exercise::
 * 2. Let parameter Type resolve to Exercise::Type naturally
 * 3. initVal() resolves to member function
 * 4. Added explicit conversion for int assignment
 */

int main() {
  Exercise ex;
  ex.setVal(3.14);  // Works with corrected version
  return 0;
}
