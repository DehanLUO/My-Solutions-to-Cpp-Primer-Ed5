/*
 * Exercise 12.20: Write a program that reads an input file a line at a time
 * into a StrBlob and uses a StrBlobPtr to print each element in that StrBlob.
 */

#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream>    // std::ifstream
#include <iostream>   // std::cin, std::cout
#include <stdexcept>  // std::exception

#include "exercise-19.h"  // StrBlob, StrBlobPtr

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
  for (auto it = blob.Begin(); it != blob.End(); it.Incr()) {
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
 * $ g++ -o main chapter-12/exercise-20.cc && ./main data/storyDataFile
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
