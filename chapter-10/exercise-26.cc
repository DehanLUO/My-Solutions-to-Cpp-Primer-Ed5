/*
 * Exercise 10.26: Explain the differences among the three kinds of insert
 * iterators. backer_inserter, front_inserter, inserter
 */

#include <deque>     // std::deque
#include <iostream>  // std::cout
#include <iterator>  // std::back_inserter, std::front_inserter, std::inserter
#include <list>      // std::list
#include <vector>    // std::vector

/*
 * Key Differences:
 * +----------------+---------------------+----------------------+
 * | Iterator Type  | Underlying Operation| Supported Containers |
 * +----------------+---------------------+----------------------+
 * | back_inserter  | push_back           | vector, deque, list  |
 * | front_inserter | push_front          | deque, list          |
 * | inserter       | insert(pos)         | All sequence         |
 * +----------------+---------------------+----------------------+
 */

/**
 * @brief Demonstrates the three insert iterator types
 */
void ExplainInsertIterators() {
  std::cout << "Insert Iterator Types:\n\n";

  // 1. back_inserter (uses push_back)
  std::cout << "1. back_inserter:\n";
  std::vector<int> vec;
  auto back_it = std::back_inserter(vec);
  *back_it = 1;  // vec.push_back(1)
  *back_it = 2;  // vec.push_back(2)
  std::cout << "Vector contents: ";
  for (int n : vec) std::cout << n << ' ';
  std::cout << "\n\n";

  // 2. front_inserter (uses push_front)
  std::cout << "2. front_inserter:\n";
  std::list<int> lst;
  auto front_it = std::front_inserter(lst);
  *front_it = 1;  // lst.push_front(1)
  *front_it = 2;  // lst.push_front(2)
  std::cout << "List contents: ";
  for (int n : lst) std::cout << n << ' ';
  std::cout << "\n\n";

  // 3. inserter (uses insert at specified position)
  std::cout << "3. inserter:\n";
  std::deque<int> deq = {1, 2};
  auto ins_it = std::inserter(deq, deq.begin() + 1);
  *ins_it = 3;  // deq.insert(position, 3)
  *ins_it = 4;  // deq.insert(position, 4)
  std::cout << "Deque contents: ";
  for (int n : deq) std::cout << n << ' ';
  std::cout << "\n\n";
}

int main() {
  ExplainInsertIterators();

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-26.cc && ./main
 * Insert Iterator Types:
 *
 * 1. back_inserter:
 * Vector contents: 1 2
 *
 * 2. front_inserter:
 * List contents: 2 1
 *
 * 3. inserter:
 * Deque contents: 1 3 4 2
 *
 */
