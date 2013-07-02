/*
 * Exercise 3.41: Write a program to initialize a vector from an array of ints.
 */

#include <iostream>  // std::cout
#include <iterator>  // std::begin, std::end
#include <vector>    // std::vector

void DumpVec(const std::vector<int>& vec) {
  for (const auto& num : vec) std::cout << num << ' ';
  std::cout << '\n';
}

int main() {
  // Original c-style array
  int scores[] = {1, 2, 3, 4, 5};

  // Method 1: Initeializer vector using pointer range
  size_t size = sizeof(scores) / sizeof(scores[0]);
  std::vector<int> score_vec1(scores, scores + size);
  DumpVec(score_vec1);

  // Method 2: Using std::begin/std::end
  std::vector<int> score_vec2(std::begin(scores), std::end(scores));
  DumpVec(score_vec2);

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-41.cc && ./main
 * 1 2 3 4 5
 * 1 2 3 4 5
 */