/*
 * Exercise 9.20: Write a program to copy elements from a list<int> into two
 * deques. The even-valued elements should go into one deque and the odd ones
 * into the other.
 */
#include <deque>     // std::deque, push_back()
#include <iostream>  // std::cout
#include <list>      // std::list, begin(), end()

/**
 * @brief Classifies and copies elements from list to even/odd deques
 * @param source_list Input list of integers to classify
 * @param even_deque Output container for even-valued elements
 * @param odd_deque Output container for odd-valued elements
 *
 * Demonstrates:
 * - Const-correctness with input parameters
 * - Efficient single-pass classification
 * - Proper use of container operations
 */
void ClassifyAndCopyElements(const std::list<int>& source_list,
                             std::deque<int>& even_deque,
                             std::deque<int>& odd_deque) {
  /*
   * Using range-based for loop for cleaner syntax
   * Automatically handles empty list case
   */
  for (const int number : source_list) {
    /*
     * Modulus operation correctly handles:
     * - Positive numbers
     * - Negative numbers
     * - Zero
     */
    if (number % 2 == 0) {
      even_deque.push_back(number);
    } else {
      odd_deque.push_back(number);
    }
  }
}

/**
 * @brief Prints container contents with descriptive header
 * @param deque The container to print
 * @param description Header text for output
 */
void PrintDeque(const std::deque<int>& deque, const std::string& description) {
  std::cout << description << " (" << deque.size() << " elements):\n";
  for (const auto& element : deque) {
    std::cout << element << ' ';
  }
  std::cout << "\n\n";
}

int main() {
  // Test data demonstrating various cases
  std::list<int> test_data = {0, 1, -2, 3, -4, 5, 6, 0, 7, -8, 9};

  std::deque<int> even_numbers;
  std::deque<int> odd_numbers;

  // Perform classification
  ClassifyAndCopyElements(test_data, even_numbers, odd_numbers);

  // Output results
  PrintDeque(even_numbers, "Even Numbers");
  PrintDeque(odd_numbers, "Odd Numbers");

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-20.cc && ./main
 * Even Numbers (6 elements):
 * 0 -2 -4 6 0 -8
 *
 * Odd Numbers (5 elements):
 * 1 3 5 7 9
 *
 */
