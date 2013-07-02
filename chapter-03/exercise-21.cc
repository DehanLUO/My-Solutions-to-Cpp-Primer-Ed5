/*
 * Exercise 3.21: Redo the first exercise from § 3.3.3 (p. 105) using iterators.
 */

#include <iostream>  // std::cout
#include <string>    // std::string
#include <vector>    // std::vector

// Generic function to dump contents of a vector with type T
template <typename T>
void Dump(const std::vector<T>& vec) {
  // Get and display the vector size
  auto size = vec.size();
  std::cout << "size: " << size;

  // Only proceed with element dumping if vector is not empty
  if (size) {
    std::cout << ", value: ";

    // Iterate through each element in the vector
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
      std::cout << *it << ' ';
    }
  }

  // End with a newline for clean output formatting
  std::cout << '\n';
}

int main() {
  using std::string;
  using std::vector;

  vector<int> v1;  // 0 elements (empty)
  Dump(v1);

  vector<int> v2(10);  // 10 elements, all 0
  Dump(v2);

  vector<int> v3(10, 42);  // 10 elements, all 42
  Dump(v3);

  vector<int> v4{10};  // 1 element: 10
  Dump(v4);

  vector<int> v5{10, 42};  //  2 elements: 10 and 42
  Dump(v5);

  vector<string> v6{10};  // 10 default-constructed strings (all empty)
  Dump(v6);

  vector<string> v7{10, "hi"};  // 10 elements, all "hi"
  Dump(v7);

  return 0;
}

/*
 * $ g++ -o main exercise-16.cc  && ./main
 * size: 0
 * size: 10, value: 0 0 0 0 0 0 0 0 0 0
 * size: 10, value: 42 42 42 42 42 42 42 42 42 42
 * size: 1, value: 10
 * size: 2, value: 10 42
 * size: 10, value:
 * size: 10, value: hi hi hi hi hi hi hi hi hi hi
 */