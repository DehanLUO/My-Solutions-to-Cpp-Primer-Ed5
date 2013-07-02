/*
 * Exercise 3.33: What would happen if we did not initialize the scores array in
 * the program on page 116?
 */

#include <iostream>  // std::cin, std::cout

#include "../include/type_util.h"  // PRINT_VAR_TYPE

constexpr uint8_t kArrSize = 10;  // Fixed array size (10 elements)

int main() {
  // count the number of grades by cluster of ten: 0-9, 10-19, ... 90-99, 100

  /*
   * If we do not initialize the scores array. It will contain garbage values
   * (whatever was in stack memory). The `++scores[...]` operation will
   * increment these random values. Final output will be meaningless numbers
   * instead of proper counts.
   */
  unsigned scores[11];  // 11 buckets. NOT INITIALIZE
  PRINT_VAR_TYPE(scores);

  unsigned grade;
  while (std::cin >> grade) {
    if (grade <= 100)
      ++scores[grade / 10];  // increment the counter for the current cluster
  }

  // Print all bucket counts (may show nonsense values)
  for (const auto& i : scores) std::cout << i << " ";

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-33.cc && ./main <<EOF
 * 1 11 21 31 41 51 61 71 81 91 99 100
 * EOF
 * scores: [3080494040, 32759, 1230844648, 32760, 139679392, 1, 1230844648, 32760, 3080495608, 32759, 124201865] |type: unsigned[11]
 * 3080494041 32760 1230844649 32761 139679393 2 1230844649 32761 3080495609 32761 124201866
 */