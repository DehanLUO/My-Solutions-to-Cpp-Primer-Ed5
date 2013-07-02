/*
 * Exercise 3.25: Rewrite the grade clustering program from § 3.3.3 (p. 104)
 * using iterators instead of subscripts.
 */

#include <iostream>  // std::cin, std::cout
#include <vector>    // std::vector

// count the number of grades by cluster of then: 0-9, 10-19, .. 90-99, 100
int main() {
  std::vector<unsigned> scores(11, 0);  // 11 buckets, all initially 0
  unsigned grade;

  auto it = scores.begin();
  while (std::cin >> grade) {  // read the grades
    if (grade <= 100)          // handle onley valid grades
      ++*(it + (grade / 10));  // increment the conuter for the current cluster
  }

  for (const auto& count : scores) {
    std::cout << count << ' ';
  }

  return 0;
}

/*
 * $  g++ -o main exercise-24.cc && ./main
 * Enter a sequence of inters: 1 2 3 4 5 6 7 8 9 10
 * 1 2 3 4 5 6 7 8 9 10 11 21 31 41 51 60 61 71 81 91 92 93 94 95 96 97 98 99
 * 100 9 2 1 1 1 1 2 1 1 9 1
 */