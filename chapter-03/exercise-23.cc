/*
 * Exercise 3.23: Write a program to create a vector with ten int elements.
 * Using an iterator, assign each element a value that is twice its current
 * value. Test your program by printing the vector.
 */

#include <iostream>  // std::cout, std::cin
#include <vector>    // std::vector

int main() {
  int input;
  std::vector<int> vec(10);  // Stores ten elements

  std::cout << "Enter ten inters:\n";  // Prompt to input 10 integers
  for (uint8_t count = 0; count < 10; ++count) {
    std::cin >> vec[count];  // Store each input in the vector
  }

  // Double each element's value using range-based for loop
  for (auto& num : vec) {  // auto& to modify the original elements
    num *= 2;              // Double the current value
  }

  // Print the modified vector
  for (const auto& num : vec) {  // const auto& to read without copying
    std::cout << num << ' ';     // Print each element followed by space
  }

  return 0;  // Successful execution
}

/*
 * $ g++ -o main exercise-23.cc && ./main
 * Enter ten inters:
 * 1 2 3 4 5 6 7 8 9 10
 * 2 4 6 8 10 12 14 16 18 20
 */