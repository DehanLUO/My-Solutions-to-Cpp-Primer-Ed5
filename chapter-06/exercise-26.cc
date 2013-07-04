/*
 * Exercise 6.26: Write a program that accepts the options presented in this
 * section. Print the values of the arguments passed to main.
 *     argv[0] = "prog"; // or argv[0] might point to an empty string
 *     argv[1] = "-d";
 *     argv[2] = "-o";
 *     argv[3] = "ofile";
 *     argv[4] = "data0";
 *     argv[5] = 0;
 */

#include <iostream>  // std::cout
#include <string>    // std::string

int main(int argc, char* argv[]) {
  // Print all arguments including program name
  std::cout << "Program received " << argc << " arguments:\n";
  for (int i = 0; i < argc; ++i) {
    std::cout << "argv[" << i << "] = " << argv[i] << '\n';
  }

  // Process options like the example scenario
  std::string output_file;
  bool debug_mode = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-d") {
      debug_mode = true;
      std::cout << "Debug mode enabled\n";
    } else if (arg == "-o") {
      if (i + 1 < argc) {         // Make sure there's another argument
        output_file = argv[++i];  // Get next argument as filename
        std::cout << "Output file specified: " << output_file << '\n';
      } else {
        std::cerr << "-o option requires a filename argument\n";
        return 1;
      }
    } else {
      std::cout << "Processing input file: " << arg << '\n';
    }
  }

  // Print final configuration
  std::cout << "\nFinal configuration:\n";
  std::cout << "Debug mode: " << (debug_mode ? "ON" : "OFF") << '\n';
  std::cout << "Output file: " << (output_file.empty() ? "none" : output_file)
            << '\n';

  return 0;
}

/* $ g++ -o prog chapter-06/exercise-26.cc && ./prog -d -o ofile data0 0
 * Program received 6 arguments:
 * argv[0] = ./prog
 * argv[1] = -d
 * argv[2] = -o
 * argv[3] = ofile
 * argv[4] = data0
 * argv[5] = 0
 * Debug mode enabled
 * Output file specified: ofile
 * Processing input file: data0
 * Processing input file: 0
 *
 * Final configuration:
 * Debug mode: ON
 * Output file: ofile
 */
