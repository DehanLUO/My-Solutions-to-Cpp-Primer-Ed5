/*
 * Exercise 12.22: What changes would need to be made to StrBlobPtr to create a
 * class that can be used with a const StrBlob? Define a class named
 * ConstStrBlobPtr that can point to a const StrBlob.
 */

#include "exercise-22.h"  // StrBlob, StrBlobPtr

#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream>    // std::ifstream
#include <iostream>   // std::cin, std::cout
#include <stdexcept>  // std::exception

/**
 * @brief Reads a file into a StrBlob and prints its contents
 * @param filename The name of the file to read
 */
void ProcessFile(const std::string& filename) {
  StrBlob blob;
  std::ifstream input(filename);

  if (!input) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  // Read file line by line into StrBlob
  std::string line;
  while (std::getline(input, line)) {
    blob.PushBack(line);
  }

  // Print contents using StrBlobPtr
  std::cout << "File contents (" << blob.Size() << " lines):\n";
  for (auto it = blob.Cbegin(); it != blob.Cend(); it.Incr()) {
    std::cout << it.Deref() << '\n';
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  try {
    ProcessFile(argv[1]);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/*
 * $ g++ -o main chapter-12/exercise-22.cc && ./main data/storyDataFile
 * File contents (10 lines):
 * Alice Emma has long flowing red hair.
 * Her Daddy says when the wind blows
 * through her hair, it looks almost alive,
 * like a fiery bird in flight.
 * A beautiful fiery bird, he tells her,
 * magical but untamed.
 * "Daddy, shush, there is no such thing,"
 * she tells him, at the same time wanting
 * him to tell her more.
 * Shyly, she asks, "I mean, Daddy, is there?"
 */
