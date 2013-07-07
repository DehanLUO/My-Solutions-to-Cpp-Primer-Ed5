/*
 * Exercise 12.29: We could have written the loop to manage the interaction with
 * the user as a do while (§ 5.4.4, p. 189) loop. Rewrite the loop to use a do
 * while. Explain which version you prefer and why.
 */

#include <cstdlib>   // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream>   // std::ifstream
#include <iostream>  // std::cin, std::cout, std::cerr
#include <string>    // std::string

#include "exercise-27.h"  // TextQuery, PrintResults()

void RunQueries(std::ifstream& infile) {
  TextQuery text_query(infile);  // Initialize query processor

  /*
   * Both versions have identical runtime characteristics
   * No memory usage differences
   * Choice is purely about code structure and readability
   * - Control flow is less intuitive: Placing the loop condition after the body
   *   of the loop can obscure the control flow. Readers must first interpret
   *   the logic of the loop body before understanding the condition that
   *   governs repetition, which may reduce clarity, especially in complex or
   *   nested code.
   */
  do {
    std::cout << "Enter word to search (q to quit): ";
    std::string word;

    if (!(std::cin >> word) || word == "q") break;

    PrintResults(std::cout, *text_query.Query(word)) << '\n';
  } while (true);  // Infinite loop with internal break
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "Error opening file: " << argv[1] << '\n';
    return EXIT_FAILURE;
  }

  RunQueries(input);

  return EXIT_SUCCESS;
}
