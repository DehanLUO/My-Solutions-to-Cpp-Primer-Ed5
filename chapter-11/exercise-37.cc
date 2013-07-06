/*
 * Exercise 11.37: What are the advantages of an unordered container as compared
 * to the ordered version of that container? What are the advantages of the
 * ordered version?
 */

/*
 * When to use unordered_map:
 * - Need fastest possible lookups
 * - Don't care about ordering
 * - Have good hash function
 * - Dealing with primitive type keys
 *
 * When to use map:
 * - Need ordered elements
 * - Require range queries
 * - Using custom objects without good hash
 * - Need predictable performance
 */

#include <chrono>         // std::chrono
#include <cstddef>        // size_t
#include <iostream>       // std::cout
#include <map>            // std::map
#include <string>         // std::string
#include <unordered_map>  // std::unordered_map

constexpr size_t kTestSize = 100000;  // Test with 100k elements

/**
 * @brief Demonstrates performance characteristics of ordered vs unordered maps
 * @param test_size Number of elements for performance comparison
 */
void CompareMapPerformance(size_t test_size) {
  std::map<std::string, int> ordered_map;
  std::unordered_map<std::string, int> unordered_map;

  // Insertion Performance Comparison
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < test_size; ++i) {
    ordered_map[std::to_string(i)] = i;
  }
  auto ordered_insert = std::chrono::high_resolution_clock::now() - start;

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < test_size; ++i) {
    unordered_map[std::to_string(i)] = i;
  }
  auto unordered_insert = std::chrono::high_resolution_clock::now() - start;

  // Lookup Performance Comparison
  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < test_size; ++i) {
    ordered_map.find(std::to_string(i));
  }
  auto ordered_lookup = std::chrono::high_resolution_clock::now() - start;

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < test_size; ++i) {
    unordered_map.find(std::to_string(i));
  }
  auto unordered_lookup = std::chrono::high_resolution_clock::now() - start;

  // Print results in scientific format (C++11 compatible)
  struct TimePrinter {
    void operator()(std::chrono::duration<double> duration,
                    const std::string& kContainerType) const {
      std::cout << kContainerType << " time: " << duration.count()
                << " seconds\n";
    }
  } print_time;

  std::cout << "=== Performance Comparison (n = " << test_size << ") ===\n";
  print_time(ordered_insert, "Ordered map insertion");
  print_time(unordered_insert, "Unordered map insertion");
  print_time(ordered_lookup, "Ordered map lookup");
  print_time(unordered_lookup, "Unordered map lookup");
}

/**
 * @brief Demonstrates key functionality differences
 */
void CompareFunctionality() {
  // Ordered Map Advantages
  std::map<std::string, int> ordered_example = {
      {"zebra", 1}, {"apple", 2}, {"banana", 3}};

  // Unordered Map Advantages
  std::unordered_map<std::string, int> unordered_example = {
      {"zebra", 1}, {"apple", 2}, {"banana", 3}};

  std::cout << "\n=== Ordered Map Iteration ===\n";
  for (const auto& pair : ordered_example) {
    std::cout << pair.first << ": " << pair.second << '\n';
  }

  std::cout << "\n=== Unordered Map Iteration ===\n";
  for (const auto& pair : unordered_example) {
    std::cout << pair.first << ": " << pair.second << '\n';
  }
}

int main() {
  CompareMapPerformance(kTestSize);
  CompareFunctionality();

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-37.cc && ./main
 * === Performance Comparison (n = 100000) ===
 * Ordered map insertion time: 0.408183 seconds
 * Unordered map insertion time: 0.0415654 seconds
 * Ordered map lookup time: 0.169989 seconds
 * Unordered map lookup time: 0.0236864 seconds
 *
 * === Ordered Map Iteration ===
 * apple: 2
 * banana: 3
 * zebra: 1
 *
 * === Unordered Map Iteration ===
 * banana: 3
 * apple: 2
 * zebra: 1
 */
