/*
 * Exercise 6.19: Given the following declarations, determine which calls are
 * legal and which are illegal. For those that are illegal, explain why.
 *     double calc(double);
 *     int count(const string &, char);
 *     int sum(vector<int>::iterator, vector<int>::iterator, int);
 *     vector<int> vec(10);
 *     (a) calc(23.4, 55.1);
 *     (b) count("abcda", ’a’);
 *     (c) calc(66);
 *     (d) sum(vec.begin(), vec.end(), 3.8);
 */

#include <string>  // std::string
#include <vector>  // std::vectpr
using std::string;
using std::vector;

// Original declarations
double calc(double);
int count(const string &, char);
int sum(vector<int>::iterator, vector<int>::iterator, int);

int main() {
  vector<int> vec(10);

  // (a) calc(23.4, 55.1);
  // Illegal: calc() takes exactly 1 argument (2 provided)

  // (b) count("abcda", 'a');
  // Legal:
  // 1. "abcda" converts to const string&
  // 2. 'a' is a valid char

  // (c) calc(66);
  // Legal:
  // 1. 66 is int but can be implicitly converted to double
  // 2. Single argument matches declaration

  // (d) sum(vec.begin(), vec.end(), 3.8);
  // Legal:
  // 1. vec.begin() and vec.end() return correct iterators
  // 2. 3.8 is double but can be implicitly converted to int
  //    (value will be truncated to 3)

  return 0;
}
