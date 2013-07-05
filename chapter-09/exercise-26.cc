/*
 * Exercise 9.26: Using the following definition of ia, copy ia into a vector
 * and into a list. Use the single-iterator form of erase to remove the elements
 * with odd values from your list and the even values from your vector.
 *     int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
 */

#include <iostream>  // std::cout
#include <list>      // std::list
#include <vector>    // std::vector

/**
 * @brief Copies array to container and removes elements based on parity
 *
 * Demonstrates:
 * - Container initialization from array
 * - Proper use of erase-remove idiom
 * - Different removal strategies for list vs vector
 */
void ProcessContainers() {
  // Original array
  int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
  const size_t ia_size = sizeof(ia) / sizeof(ia[0]);

  // Copy array to vector (removing evens later)
  std::vector<int> vec(ia, ia + ia_size);

  // Copy array to list (removing odds later)
  std::list<int> lst(ia, ia + ia_size);

  /*
   * List processing - remove odd elements
   * Using single-iterator erase (safe for lists)
   */
  auto list_it = lst.begin();
  while (list_it != lst.end()) {
    if (*list_it % 2 != 0) {         // if odd
      list_it = lst.erase(list_it);  // erase and get next
    } else {
      ++list_it;
    }
  }

  /*
   * Vector processing - remove even elements
   * Using erase-remove idiom (more efficient for vectors)
   */
  vec.erase(
      std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; }),
      vec.end());

  /* Output results */
  std::cout << "List after removing odds (evens remain):\n";
  for (int num : lst) std::cout << num << " ";
  std::cout << "\n\n";

  std::cout << "Vector after removing evens (odds remain):\n";
  for (int num : vec) std::cout << num << " ";
  std::cout << "\n";
}

int main() {
  ProcessContainers();

  return 0;
}
/*
 * $ g++ -o main chapter-09/exercise-26.cc && ./main
 * List after removing odds (evens remain):
 * 0 2 8
 *
 * Vector after removing evens (odds remain):
 * 1 1 3 5 13 21 55 89
 */
