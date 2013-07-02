/*
 * Exercise 3.14: Write a program to read a sequence of ints from cin and store
 * those values in a vector.
 */

#include <iostream>  // std::cin, std::cout
#include <vector>    // std::vector

int main() {
  std::vector<int> vec;  // vector to store the integers
  int num;               // variable to hold each input number

  std::cout << "Enter a sequence of inters: ";

  // Read integers until end-of-file or invalid input
  while (std::cin >> num) {
    vec.emplace_back(num);  // Add each integer to the vector
  }

  // Print the vector contents to verify
  for (const auto item : vec) {
    std::cout << item << ' ';
  }
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise-14.cc  && ./main
 * Enter a sequence of inters: 1 1 2 3 5 8 13 21 34
 * 1 1 2 3 5 8 13 21 34
 */