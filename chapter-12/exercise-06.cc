/*
 * Exercise 12.6: Write a function that returns a dynamically allocated vector
 * of ints. Pass that vector to another function that reads the standard input
 * to give values to the elements. Pass the vector to another function to print
 * the values that were read. Remember to delete the vector at the appropriate
 * time.
 */

#include <cstddef>   // size_t
#include <iostream>  // std::cin, std::cout
#include <vector>    // std::vector

/**
 * @brief Creates and returns a dynamically allocated vector of ints
 * @param size The number of elements to allocate
 * @return Pointer to the newly allocated vector
 */
std::vector<int>* CreateDynamicVector(size_t size) {
  return new std::vector<int>(size);  // Value-initialized elements
}

/**
 * @brief Reads values from standard input into a vector
 * @param vec_ptr Pointer to the vector to populate
 */
void ReadIntoVector(std::vector<int>* vec_ptr) {
  if (nullptr == vec_ptr) return;  // Safety check

  std::cout << "Enter " << vec_ptr->size() << " integers:\n";
  for (auto& elem : *vec_ptr) {
    std::cin >> elem;
  }
}

/**
 * @brief Prints the contents of a vector
 * @param vec_ptr Pointer to the vector to print
 */
void PrintVector(const std::vector<int>* vec_ptr) {
  if (nullptr == vec_ptr) return;  // Safety check

  std::cout << "Vector elements:";
  for (const auto& elem : *vec_ptr) {
    std::cout << ' ' << elem;
  }
  std::cout << '\n';
}

int main() {
  const size_t vector_size = 5;

  // Create the vector
  auto numbers = CreateDynamicVector(vector_size);

  // Read values into it
  ReadIntoVector(numbers);

  // Print the values
  PrintVector(numbers);

  // Clean up
  delete numbers;
  numbers = nullptr;  // Good practice

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-06.cc && ./main
 * Enter 5 integers:
 * 0 1 1 2 3
 * Vector elements: 0 1 1 2 3
 */
