/*
 * Exercise 9.39: Explain what the following program fragment does:
 *     vector<string> svec;
 *     svec.reserve(1024);
 *     string word;
 *     while (cin >> word)
 *       svec.push_back(word);
 *     svec.resize(svec.size() + svec.size() / 2);
 */

#include <iostream>  // std::cin
#include <vector>    // std::vector

int main() {
  // A vector of string objects named svec is created. Initially, it is empty
  // and has minimal capacity (0)
  std::vector<std::string> svec;

  // This call pre-allocates memory for at least 1024 elements. It does not
  // change the size() of the vector. The purpose is to improve performance by
  // avoiding frequent reallocations during push_back
  svec.reserve(1024);

  // Words are read from cin, one at a time, until input ends. Each word is
  // appended to svec using push_back. If the number of words exceeds 1024, svec
  // will automatically reallocate additional storage beyond the reserved
  // capacity.
  std::string word;
  while (std::cin >> word) svec.push_back(word);

  // This increases the size of the vector by 50%.
  svec.resize(svec.size() + (svec.size() / 2));

  return 0;
}
