/*
 * Exercise 12.7: Redo the previous exercise, this time using shared_ptr.
 */

#include <cstddef>   // size_t
#include <iostream>  // std::cin, std::cout
#include <memory>    // std::shared_ptr
#include <vector>    // std::vector

/**
 * @brief Creates and returns a shared_ptr to a vector of ints
 * @param size The number of elements to allocate
 * @return shared_ptr to the newly allocated vector
 */
std::shared_ptr<std::vector<int>> CreateSharedVector(size_t size) {
  return std::make_shared<std::vector<int>>(size);
}

/**
 * @brief Reads values from standard input into a vector
 * @param vec Shared pointer to the vector to populate
 */
void ReadIntoVector(std::shared_ptr<std::vector<int>> vec) {
  if (!vec) return;  // Safety check

  std::cout << "Enter " << vec->size() << " integers:\n";
  for (auto& elem : *vec) {
    std::cin >> elem;
  }
}

/**
 * @brief Prints the contents of a vector
 * @param vec Shared pointer to the vector to print
 */
void PrintVector(const std::shared_ptr<std::vector<int>>& vec) {
  if (!vec) return;  // Safety check

  std::cout << "Vector elements:";
  for (const auto& elem : *vec) {
    std::cout << ' ' << elem;
  }
  std::cout << '\n';
}

int main() {
  const size_t vector_size = 5;

  // Create the vector using shared_ptr
  auto numbers = CreateSharedVector(vector_size);

  // Read values into it
  ReadIntoVector(numbers);

  // Print the values
  PrintVector(numbers);

  // No explicit delete needed - shared_ptr handles cleanup automatically
  // when last reference goes out of scope

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-07.cc && ./main
 * Enter 5 integers:
 * 0 1 1 2 3
 * Vector elements: 0 1 1 2 3
 */
