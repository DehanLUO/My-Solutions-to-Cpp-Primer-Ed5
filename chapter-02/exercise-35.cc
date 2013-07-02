/*
 * Exercise 2.35: Determine the types deduced in each of the following
 * definitions. Once you’ve figured out the types, write a program to see
 * whether you were correct.
 *     const int i = 42;
 *     auto j = i;
 *     const auto &k = i;
 *     auto p = &i;
 *     const auto j2 = i, &k2 = i;
 */

#include "../include/type_util.h"

int main() {
  const int i = 42;  // `i` is a const int
  PRINT_VAR_TYPE(i);

  auto j = i;  // `j` is an int (top-level const in i is dropped)
  PRINT_VAR_TYPE(j);

  const auto &k = i;  // `k` is a reference to const int
  PRINT_VAR_TYPE(k);

  // `p` is a pointer to const int (& of an const int object is const int*)
  auto p = &i;
  PRINT_VAR_TYPE(p);

  // `j2` is a const int.
  // `k2` is a reference to const int.
  const auto j2 = i, &k2 = i;
  PRINT_VAR_TYPE(j2);
  PRINT_VAR_TYPE(k2);

  return 0;
}

/*
 * $ g++ -o main exercise-35.cc && ./main
 * i=42 |type: int const
 * j=42 |type: int
 * k=42 |type: int const &
 * p(0x7ff7bde19c58) |type: int const *
 * j2=42 |type: int const
 * k2=42 |type: int const &
 */