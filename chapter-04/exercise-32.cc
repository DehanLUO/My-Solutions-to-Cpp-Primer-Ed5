// Exercise 4.32: Explain the following loop.
//     constexpr int size = 5;
//     int ia[size] = {1,2,3,4,5};
//     for (int *ptr = ia, ix = 0;
//          ix != size && ptr != ia+size;
//          ++ix, ++ptr) { /* . . . */ }

#include <iostream>  // std::cout

/**
 * @brief Demonstrates pointer-array relationship and loop conditions
 */
void ExplainArrayTraversal() {
  // constexpr indicates compile-time constant
  constexpr int size = 5;

  // list-initialization
  int ia[size] = {1, 2, 3, 4, 5};

  // Loop explanation:
  // - Initialization: ptr points to ia[0], ix starts at 0
  // - Condition: Continues while BOTH:
  //   1. ix hasn't reached size (array bound check)
  //   2. ptr hasn't advanced past ia+size (pointer validity check)
  // - Increment: Advances BOTH index and pointer in lockstep
  for (int *ptr = ia, ix = 0; ix != size && ptr != ia + size; ++ix, ++ptr) {
    std::cout << "Index: " << ix << " Pointer points to: " << *ptr << '\n';
  }
}

int main() {
  ExplainArrayTraversal();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-32.cc && ./main
 * Index: 0 Pointer points to: 1
 * Index: 1 Pointer points to: 2
 * Index: 2 Pointer points to: 3
 * Index: 3 Pointer points to: 4
 * Index: 4 Pointer points to: 5
 */
