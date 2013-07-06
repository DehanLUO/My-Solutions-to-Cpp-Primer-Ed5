/*
 * Exercise 11.17: Assuming c is a multiset of strings and v is a vector of
 * strings, explain the following calls. Indicate whether each call is legal:
 *     copy(v.begin(), v.end(), inserter(c, c.end()));
 *     copy(v.begin(), v.end(), back_inserter(c));
 *     copy(c.begin(), c.end(), inserter(v, v.end()));
 *     copy(c.begin(), c.end(), back_inserter(v));
 */

#include <algorithm>
#include <iostream>  // std::cout
#include <iterator>  // std::inserter, std::back_inserter
#include <set>       // std::set
#include <vector>    // std::vector

int main() {
  std::multiset<std::string> c = {"apple", "banana"};
  std::vector<std::string> v = {"cherry", "date"};

  // 1. Legal - copies from vector to multiset using insert_iterator
  std::copy(v.begin(), v.end(), std::inserter(c, c.end()));
  std::cout << "After copy 1, multiset contains: ";
  for (const auto& s : c) std::cout << s << " ";
  std::cout << '\n';

  // 2. Illegal - multiset doesn't have push_back
  // std::copy(v.begin(), v.end(), std::back_inserter(c));  // Won't compile

  // 3. Legal - copies from multiset to vector using insert_iterator
  std::copy(c.begin(), c.end(), std::inserter(v, v.end()));
  std::cout << "After copy 3, vector contains: ";
  for (const auto& s : v) std::cout << s << " ";
  std::cout << '\n';

  // 4. Legal - copies from multiset to vector using back_inserter
  std::copy(c.begin(), c.end(), std::back_inserter(v));
  std::cout << "After copy 4, vector contains: ";
  for (const auto& s : v) std::cout << s << " ";
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-17.cc && ./main
 * After copy 1, multiset contains: apple banana cherry date
 * After copy 3, vector contains: cherry date apple banana cherry date
 * After copy 4, vector contains: cherry date apple banana cherry date apple banana cherry date
 */
