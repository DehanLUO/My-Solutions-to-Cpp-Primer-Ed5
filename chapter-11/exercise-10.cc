/*
 * Exercise 11.10: Could we define a map from vector<int>::iterator to int? What
 * about from list<int>::iterator to int? In each case, if not, why not?
 */

#include <iostream>  //  std::cout
#include <list>      // std::list
#include <map>       // std::map
#include <vector>    // std::vector

int main() {
  // 1. vector<int>::iterator to int - VALID
  std::map<std::vector<int>::iterator, int> vector_iter_map;

  std::cout << "Key Differences:\n";

  // Vector iterator map works because vector iterators are comparable
  std::vector<int> vec = {1, 2, 3};
  vector_iter_map[vec.begin()] = 10;
  vector_iter_map[vec.begin() + 1] = 20;

  std::cout << "Vector iterator map:\n";
  for (const auto& pair : vector_iter_map) {
    std::cout << "Iterator points to: " << *pair.first
              << ", mapped value: " << pair.second << '\n';
  }

  // 2. list<int>::iterator to int - INVALID (without custom comparator)
  /*
   * Why list iterator map doesn't work by default:
   * - vector iterators are RandomAccessIterators - support full comparison
   * - list iterators are BidirectionalIterators - only support ==/!=
   * - map requires keys to be ordered with < operator
   */
  // std::map<std::list<int>::iterator, int> list_iter_map;  // Won't compile

  // Workaround for list iterators
  struct ListIterComparator {
    bool operator()(const std::list<int>::iterator& lhs,
                    const std::list<int>::iterator& rhs) const {
      // Compare the actual memory addresses as a proxy
      return &*lhs < &*rhs;
    }
  };

  std::map<std::list<int>::iterator, int, ListIterComparator> list_iter_map;
  std::list<int> lst = {4, 5, 6};
  list_iter_map[lst.begin()] = 100;
  list_iter_map[std::next(lst.begin())] = 200;

  std::cout << "List iterator map (with custom comparator):\n";
  for (const auto& pair : list_iter_map) {
    std::cout << "Iterator points to: " << *pair.first
              << ", mapped value: " << pair.second << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-10.cc && ./main
 * Key Differences:
 * Vector iterator map:
 * Iterator points to: 1, mapped value: 10
 * Iterator points to: 2, mapped value: 20
 * List iterator map (with custom comparator):
 * Iterator points to: 4, mapped value: 100
 * Iterator points to: 5, mapped value: 200
 */
