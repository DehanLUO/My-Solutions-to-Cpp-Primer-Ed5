/*
 * Exercise 12.30: Define your own versions of the TextQuery and QueryResult
 * classes and execute the runQueries function from § 12.3.1 (p. 486).
 */

#include <cstdlib>   // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream>   // std::ifstream
#include <iostream>  // std::cin, std::cout, std::cerr
#include <string>    // std::string

#include "exercise-27.h"  // TextQuery, PrintResults()

void RunQueries(std::ifstream& infile) {
  TextQuery text_query(infile);  // Initialize query processor

  while (true) {
    std::cout << "Enter word to search (q to quit): ";
    std::string word;

    if (!(std::cin >> word) || word == "q") break;

    PrintResults(std::cout, *text_query.Query(word)) << '\n';
  }
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

/*
 * $ g++ -o main chapter-12/exercise-30.cc && ./main  data/storyDataFile
 * Enter word to search (q to quit): her
 * Query Word: "her" found 4 times
 * (line 2) Her Daddy says when the wind blows
 * (line 3) through her hair, it looks almost alive,
 * (line 5) A beautiful fiery bird, he tells her,
 * (line 9) him to tell her more.
 *
 * Enter word to search (q to quit): q
 */
