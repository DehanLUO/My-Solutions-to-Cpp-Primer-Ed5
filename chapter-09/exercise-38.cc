/*
 * Exercise 9.38: Write a program to explore how vectors grow in the library you
 * use.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vetcor

/**
 * @brief Entry point of the program.
 */
int main() {
  std::vector<int> vec;
  std::size_t previous_capacity = vec.capacity();

  std::cout << "Observing std::vector capacity growth:\n";
  std::cout << "---------------------------------------\n";
  std::cout << "Size\tCapacity\n";

  for (int i = 0; i < 10000; ++i) {
    vec.push_back(i);
    if (vec.capacity() != previous_capacity) {
      std::cout << vec.size() << "\t" << vec.capacity() << '\n';
      previous_capacity = vec.capacity();
    }
  }

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-38.cc && ./main
 * Observing std::vector capacity growth:
 * ---------------------------------------
 * Size Capacity
 * 1    1
 * 2    2
 * 3    4
 * 5    8
 * 9    16
 * 17   32
 * 33   64
 * 65   128
 * 129  256
 * 257  512
 * 513  1024
 * 1025 2048
 * 2049 4096
 * 4097 8192
 * 8193 16384
 */
