/*
 * Exercise 9.13: How would you initialize a vector<double> from a list<int>?
 * From a vector<int>? Write code to check your answers.
 */

#include <iostream>  // std::cout
#include <list>      // std::list
#include <vector>    // std::vector

/**
 * @brief Demonstrates initialization of vector<double> from integer containers
 */
void DemonstrateConversions() {
  // Source containers
  std::list<int> int_list{1, 2, 3, 4, 5};
  std::vector<int> int_vec{6, 7, 8, 9, 10};

  // 1. From list<int> using iterator range constructor
  std::vector<double> dbl_vec1(int_list.begin(), int_list.end());

  // 2. From vector<int> using iterator range constructor
  std::vector<double> dbl_vec2(int_vec.begin(), int_vec.end());

  // Print results
  auto print_vector = [](const std::vector<double>& v) {
    for (auto val : v) std::cout << val << ' ';
    std::cout << '\n';
  };

  std::cout << "From list<int>: ";
  print_vector(dbl_vec1);  // 1 2 3 4 5

  std::cout << "From vector<int>: ";
  print_vector(dbl_vec2);  // 6 7 8 9 10
}

int main() {
  DemonstrateConversions();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-13.cc && ./main
 * From list<int>: 1 2 3 4 5
 * From vector<int>: 6 7 8 9 10
 */
