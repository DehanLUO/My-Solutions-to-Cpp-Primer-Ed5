/*
 * Exercise 9.23: In the first program in this section on page 346, what would
 * the values of val, val2, val3, and val4 be if c.size() is 1?
 *     // check that there are elements before dereferencing an iterator or
 *     // calling front or back
 *     if (!c.empty()) {
 *       // val and val2 are copies of the value of the first element in c
 *       auto val = *c.begin(), val2 = c.front();
 *       // val3 and val4 are copies of the last element in c
 *       auto last = c.end();
 *       auto val3 = *(--last); // can't decrement forward_list iterators
 *       auto val4 = c.back(); // not supported by forward_list
 *     }
 */

#include <iostream>  // std::cout
#include <list>      // std::list
#include <vector>    // std::vector

/**
 * @brief Demonstrates container value access when size() == 1
 *
 * Shows behavior of front/back and iterator dereferencing
 * when container has exactly one element
 */
void DemonstrateSingleElementAccess() {
  std::vector<int> c = {42};  // Single-element container

  if (!c.empty()) {
    /*
     * Case when c.size() == 1:
     * - begin() == end() - 1
     * - front() == back()
     * - All values will be identical
     */
    auto val = *c.begin();  // 42 (dereference begin iterator)
    auto val2 = c.front();  // 42 (first element)

    auto last = c.end();
    auto val3 = *(--last);  // 42 (decrement end iterator)
    auto val4 = c.back();   // 42 (last element)

    /*
     * All values are copies of the single element's value
     * Proof through output and address comparison
     */
    std::cout << "Values when size() == 1:\n"
              << "val: " << val << "\n"
              << "val2: " << val2 << "\n"
              << "val3: " << val3 << "\n"
              << "val4: " << val4 << "\n";

    /*
     * Address comparison shows they're distinct copies:
     * - &val != &c.front()
     * - Each is an independent copy
     */
    std::cout << "\nAddress comparison:\n"
              << "&val: " << &val << " vs &c.front(): " << &c.front() << "\n";
  }
}

/**
 * @brief Additional verification with different container types
 */
template <typename Container>
void VerifySingleElementBehavior() {
  Container c = {100};  // Single element

  auto val = *c.begin();
  auto val2 = c.front();

  auto last = c.end();
  auto val3 = *(--last);
  auto val4 = c.back();  // Won't compile for forward_list

  std::cout << val << " " << val2 << " " << val3 << " " << val4 << "\n";
}

int main() {
  // Primary demonstration
  DemonstrateSingleElementAccess();

  // Additional verification
  VerifySingleElementBehavior<std::vector<int>>();
  VerifySingleElementBehavior<std::list<int>>();
  // VerifySingleElementBehavior<std::forward_list<int>>(); // Won't compile (no
  // back())

  return 0;
}
/*
 * $ g++ -o main chapter-09/exercise-23.cc && ./main
 * Values when size() == 1:
 * val: 42
 * val2: 42
 * val3: 42
 * val4: 42
 *
 * Address comparison:
 * &val: 0x7ff7bcd86c10 vs &c.front(): 0x600001c9c050
 *
 * 100 100 100 100
 *
 * 100 100 100 100
 */
