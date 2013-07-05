/*
 * Exercise 9.12: Explain the differences between the constructor that takes a
 * container to copy and the constructor that takes two iterators.
 */

/*
 * Exercise 9.12 Solution
 * Container copy vs iterator range constructors
 * Standard: ISO/IEC 14882:2017 §26.2 (Container requirements)
 */

#include <iostream>  // std::cout
#include <list>      // std::list
#include <vector>    // std::vector

/**
 * @brief Key differences between container copy and iterator range constructors
 *
 * 1. Constructor Syntax:
 *    - Copy: vector(const vector& other)
 *    - Iterator range: template<class InputIt> vector(InputIt first, InputIt
 *      last)
 * 2. Parameter Types:
 *    - Copy: Takes exact container type
 *    - Iterator range: Takes any iterator pair
 * 3. Flexibility:
 *    - Copy: Only works with same container type
 *    - Iterator range: Works with any compatible range
 * 4. Use Cases:
 *    - Copy: When duplicating entire container
 *    - Iterator range: When copying partial range or different container type
 */

void DemonstrateVectorCnstructors() {
  std::vector<int> source_vec{1, 2, 3, 4, 5};
  std::list<int> source_list{6, 7, 8, 9, 10};

  // 1. Container copy constructor - exact type match required
  std::vector<int> copied_vec(source_vec);  // OK: same type
  // std::vector<int> bad_copy(source_list); // Error: type mismatch

  // 2. Iterator range constructor - works with any compatible iterators
  std::vector<int> range_vec1(source_vec.begin(),
                              source_vec.end());  // From vector
  std::vector<int> range_vec2(source_list.begin(),
                              source_list.end());  // From list
  std::vector<int> partial_vec(source_vec.begin() + 1,
                               source_vec.end() - 1);  // Subrange

  // Print results
  auto print = [](const auto& container) {
    for (auto val : container) std::cout << val << ' ';
    std::cout << '\n';
  };

  std::cout << "Copied vector: ";
  print(copied_vec);  // 1 2 3 4 5

  std::cout << "Range from vector: ";
  print(range_vec1);  // 1 2 3 4 5

  std::cout << "Range from list: ";
  print(range_vec2);  // 6 7 8 9 10

  std::cout << "Partial range: ";
  print(partial_vec);  // 2 3 4
}

int main() {
  DemonstrateVectorCnstructors();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-12.cc && ./main
 * Copied vector: 1 2 3 4 5
 * Range from vector: 1 2 3 4 5
 * Range from list: 6 7 8 9 10
 * Partial range: 2 3 4
 */
