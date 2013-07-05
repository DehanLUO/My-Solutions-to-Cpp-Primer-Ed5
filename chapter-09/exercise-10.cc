/*
 * Exercise 9.10: What are the types of the following four objects?
 *     vector<int> v1;
 *     const vector<int> v2;
 *     auto it1 = v1.begin(), it2 = v2.begin();
 *     auto it3 = v1.cbegin(), it4 = v2.cbegin();
 */

#include <vector>  // std::vector

int main() {
  std::vector<int> v1;
  const std::vector<int> v2;

  /*
   * error: The initializers must provide consistent auto-deduced types. Type
   * decuced from it1 is std::vector<int>::iteraotr; type deduced from it2 is
   * std::vector<int>::const_iterator. Inconsistent types for it1 and it2.
   */
  // auto it1 = v1.begin(), it2 = v2.begin();

  auto it1 = v1.begin();  // std::vector<int>::iterator
  auto it2 = v2.begin();  // std::vector<int>::const_iterator

  auto it3 = v1.cbegin(),  //   std::vector<int>::const_iterator
      it4 = v2.cbegin();   //   std::vector<int>::const_iterator

  return 0;
}
