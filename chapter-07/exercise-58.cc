/*
 * Exercise 7.58: Which, if any, of the following static data member
 * declarations and definitions are errors? Explain why.
 *     // example.h
 *     class Example {
 *      public:
 *       static double rate = 6.5;
 *       static const int vecSize = 20;
 *       static vector<double> vec(vecSize);
 *     };
 *     // example.C
 *     #include "example.h"
 *     double Example::rate;
 *     vector<double> Example::vec;
 */

#include <vector>  // std::vector

/*
 * 1. static double rate = 6.5;
 *    - Error: Non-const static cannot be initialized in-class
 *      Header: static double rate;
 *      Source: double Example::rate = 6.5;
 *
 * 2. static const int vecSize = 20;
 *    - Valid: Integral static const can be initialized in-class
 *
 * 3. static vector<double> vec(vecSize);
 *    - Error: Cannot use constructor syntax in-class
 *      Header: static vector<double> vec;
 *      Source: vector<double> Example::vec(vecSize);
 */

/**
 * @brief Corrected implementation
 */
// example.h
class Example {
 public:
  static double rate;              // Declaration only
  static const int vecSize = 20;   // Valid constexpr
  static std::vector<double> vec;  // Declaration
};

// example.cpp
double Example::rate = 6.5;                          // Definition with init
std::vector<double> Example::vec(Example::vecSize);  // Proper construction
