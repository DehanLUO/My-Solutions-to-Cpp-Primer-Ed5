/*
 * Exercise 3.2: Write a program to read the standard input a line at a time.
 * Modify your program to read a word at a time.
 */

#include <iostream>  // std::getline, std::cin
#include <string>    // std::string

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::cout << line << '\n';
  }
  return 0;
}

/*
 * $ g++ -o main exercise-02-a.cc && ./main < ../data/book_sales
 * 0-201-70353-X 4 24.99
 * 0-201-82470-1 4 45.39
 * 0-201-88954-4 2 15.00
 * 0-201-88954-4 5 12.00
 * 0-201-88954-4 7 12.00
 * 0-201-88954-4 2 12.00
 * 0-399-82477-1 2 45.39
 * 0-399-82477-1 3 45.39
 * 0-201-78345-X 3 20.00
 * 0-201-78345-X 2 25.00
 */