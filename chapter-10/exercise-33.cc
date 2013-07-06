/*
 * Exercise 10.33: Write a program that takes the names of an input file and two
 * output files. The input file should hold integers. Using an istream_iterator
 * read the input file. Using ostream_iterators, write the odd numbers into the
 * first output file. Each value should be followed by a space. Write the even
 * numbers into the second file. Each of these values should be placed on a
 * separate line.
 */

#include <fstream>   // std::ifstream, std::ofstream
#include <iostream>  // std::cerr
#include <iterator>  // std::istream_iterator, std::ostream_iterator

int main(int argc, char* argv[]) {
  // Check command line arguments
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0]
              << " <input_file> <odd_output_file> <even_output_file>\n";
    return 1;
  }

  // Open input file
  std::ifstream in(argv[1]);
  if (!in) {
    std::cerr << "Error opening input file: " << argv[1] << '\n';
    return 2;
  }

  // Open output files
  std::ofstream odd_out(argv[2]);
  std::ofstream even_out(argv[3]);
  if (!odd_out || !even_out) {
    std::cerr << "Error opening output files\n";
    return 3;
  }

  // Create stream iterators
  std::istream_iterator<int> in_iter(in), eof;
  std::ostream_iterator<int> odd_iter(odd_out, " ");
  std::ostream_iterator<int> even_iter(even_out, "\n");

  // Process numbers
  while (in_iter != eof) {
    if (*in_iter % 2 != 0) {
      *odd_iter++ = *in_iter++;  // Write odd numbers with spaces
    } else {
      *even_iter++ = *in_iter++;  // Write even numbers with newlines
    }
  }

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-33.cc && ./main data/absInt {odd,even}_out
 * $ cat odd_out
 * 65 -95 39 -67 95 83 -93
 * $ cat even_out
 * -42
 * 100
 * 76
 * -88
 * 76
 * 92
 * 76
 * 0
 */
