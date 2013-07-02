/*
 * Exercise 3.38: In this section, we noted that it was not only illegal but
 * meaningless to try to add two pointers. Why would adding two pointers be
 * meaningless?
 */

#include <iostream>  // std::cout

int main() {
  //
  int arr[] = {10, 20, 30};
  int *p1 = &arr[0];  // Points to 10
  int *p2 = &arr[2];  // Points to 30

  ptrdiff_t distance = p2 - p1;  // Legal: gives 2 (element apart)
  std::cout << "Distance: " << distance << '\n';

  /*
   * Adding two pointers does not make logical sense because pointers represent
   * memory addresses. While subtracting them gives the distances (offset)
   * between two objects, adding them would produce a nonsensical memory
   * location with no real-world meaning. The c++ standard forbids it to prevent
   * buggy code.
   */
  // int *p3 = p1 + p2;

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-36.cc && ./main
 * Distance: 2
 */