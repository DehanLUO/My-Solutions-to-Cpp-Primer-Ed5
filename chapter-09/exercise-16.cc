/*
 * Exercise 9.16: Repeat the previous program, but compare elements in a
 * list<int> to a vector<int>.
 */

#include <algorithm>  // std::equal
#include <list>       // std::list
#include <vector>     // std::vector

/**
 * @brief Compares elements between list<int> and vector<int>
 *
 * Demonstrates three comparison methods between different container types:
 * 1. Using std::equal with begin/end iterators
 * 2. Manual element-by-element comparison
 * 3. Container conversion then direct comparison
 */
void CompareListAndVector() {
  std::list<int> test_list{1, 2, 3, 4, 5};
  std::vector<int> test_vec{1, 2, 3, 4, 5};
  std::vector<int> diff_vec{1, 2, 3};

  /*
   * Method 1: Using std::equal algorithm
   * Preferred when comparing different container types
   */
  bool method1_same = std::equal(test_list.begin(), test_list.end(),
                                 test_vec.begin(), test_vec.end());
  bool method1_diff = std::equal(test_list.begin(), test_list.end(),
                                 diff_vec.begin(), diff_vec.end());

  /*
   * Method 2: Manual element comparison
   * Demonstrates iterator usage and length check
   */
  bool method2_same = true;
  if (test_list.size() != test_vec.size()) {
    method2_same = false;
  } else {
    auto lit = test_list.begin();
    auto vit = test_vec.begin();
    while (lit != test_list.end()) {
      if (*lit != *vit) {
        method2_same = false;
        break;
      }
      ++lit;
      ++vit;
    }
  }

  /*
   * Method 3: Container conversion
   * Converts list to vector then uses operator==
   * Note: Creates temporary copy
   */
  std::vector<int> temp_vec(test_list.begin(), test_list.end());
  bool method3_same = (temp_vec == test_vec);
  bool method3_diff = (temp_vec == diff_vec);
}

int main() {
  // Exercise 9.16 solution demonstration
  CompareListAndVector();

  return 0;
}
