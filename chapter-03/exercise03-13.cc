/*
 * Exercise 3.13: How many elements are there in each of the following vectors?
 * What are the values of the elements?
 * (a) vector<int> v1;
 * (b) vector<int> v2(10);
 * (c) vector<int> v3(10, 42);
 * (d) vector<int> v4{10};
 * (e) vector<int> v5{10, 42};
 * (f) vector<string> v6{10};
 * (g) vector<string> v7{10, "hi"};
 */

#include <string>  // std::string
#include <vector>  // std::vector

int main() {
  using std::string;
  using std::vector;

  vector<int> v1;               // 0 elements (empty)
  vector<int> v2(10);           // 10 elements, all 0
  vector<int> v3(10, 42);       // 10 elements, all 42
  vector<int> v4{10};           // 1 element: 10
  vector<int> v5{10, 42};       //  2 elements: 10 and 42
  vector<string> v6{10};        // 10 default-constructed strings (all empty)
  vector<string> v7{10, "hi"};  // 10 elements, all "hi"

  return 0;
}
