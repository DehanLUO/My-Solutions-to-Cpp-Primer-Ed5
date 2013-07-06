/*
 * Exercise 10.28: Copy a vector that holds the values from 1 to 9 inclusive,
 * into three other containers. Use an inserter, a back_inserter, and a
 * front_inserter, respectivly to add elements to these containers. Predict how
 * the output sequence varies by the kind of inserter and verify your
 * predictions by running your programs.
 */

#include <algorithm>  // std::copy
#include <deque>      // std::deque
#include <iostream>   // std::cout
#include <iterator>   // std::back_inserter, std::front_inserter, std::inserter
#include <list>       // std::list
#include <vector>     // std::vector

/**
 * @brief Prints container contents with description
 */
template <typename Container>
void PrintContainer(const std::string& description, const Container& c) {
  std::cout << description << ": ";
  for (const auto& elem : c) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main() {
  // Original vector with values 1-9
  std::vector<int> original = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Three destination containers
  std::list<int> lst_inserter;
  std::vector<int> vec_back;
  std::deque<int> deq_front;

  // 1. Using inserter (maintains original order)
  std::copy(original.begin(), original.end(),
            std::inserter(lst_inserter, lst_inserter.begin()));

  // 2. Using back_inserter (maintains original order)
  std::copy(original.begin(), original.end(), std::back_inserter(vec_back));

  // 3. Using front_inserter (reverses order)
  std::copy(original.begin(), original.end(), std::front_inserter(deq_front));

  // Print results
  PrintContainer("Original vector", original);
  PrintContainer("List (inserter)  ", lst_inserter);
  PrintContainer("Vector (back_inserter)", vec_back);
  PrintContainer("Deque (front_inserter)", deq_front);

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-28.cc && ./main
 * Original vector: 1 2 3 4 5 6 7 8 9
 * List (inserter)  : 1 2 3 4 5 6 7 8 9
 * Vector (back_inserter): 1 2 3 4 5 6 7 8 9
 * Deque (front_inserter): 9 8 7 6 5 4 3 2 1
 */
