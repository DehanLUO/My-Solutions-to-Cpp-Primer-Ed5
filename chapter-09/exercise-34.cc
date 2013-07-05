/*
 * Exercise 9.34: Assuming vi is a container of ints that includes even and odd
 * values, predict the behavior of the following loop. After you’ve analyzed
 * this loop, write a program to test whether your expectations were correct.
 *     iter = vi.begin();
 *     while (iter != vi.end())
 *       if (*iter % 2)
 *         iter = vi.insert(iter, *iter);
 *       ++iter;
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

void TestProblematicLoop() {
  std::vector<int> vi = {0, 1, 2, 3, 4, 5};
  auto iter = vi.begin();

  std::cout << "Initial: ";
  for (int num : vi) std::cout << num << ' ';
  std::cout << '\n';

  // The problematic loop
  while (iter != vi.end()) {
    if (*iter % 2) {
      std::cout << "Inserting before " << *iter << '\n';
      iter = vi.insert(iter, *iter);
      // Missing ++iter here would be correct
    }
    ++iter;  // Unconditional increment

    // Safety check to prevent infinite loop
    if (vi.size() > 11) {
      std::cout << "Breaking infinite loop\n";
      break;
    }
  }

  std::cout << "Result: ";
  for (int num : vi) std::cout << num << ' ';
  std::cout << '\n';
}

void CorrectedVersion() {
  std::vector<int> vi = {0, 1, 2, 3, 4, 5};
  auto iter = vi.begin();

  while (iter != vi.end()) {
    if (*iter % 2) {
      iter = vi.insert(iter, *iter);
      ++iter;  // Skip the duplicate we just inserted
    }
    ++iter;  // Move to next element
  }

  std::cout << "Corrected: ";
  for (int num : vi) std::cout << num << ' ';
  std::cout << '\n';
}

int main() {
  std::cout << "=== Problematic Version ===\n";
  TestProblematicLoop();

  std::cout << "\n=== Corrected Version ===\n";
  CorrectedVersion();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-34.cc && ./main
 * === Problematic Version ===
 * Initial: 0 1 2 3 4 5
 * Inserting before 1
 * Inserting before 1
 * Inserting before 1
 * Inserting before 1
 * Inserting before 1
 * Inserting before 1
 * Breaking infinite loop
 * Result: 0 1 1 1 1 1 1 1 2 3 4 5
 *
 * === Corrected Version ===
 * Corrected: 0 1 1 2 3 3 4 5 5
 */
