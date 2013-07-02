/*
 * Exercise 3.16: Write a program to print the size and contents of the vectors
 * from exercise 3.13. Check whether your answers to that exercise were correct.
 * If not, restudy § 3.3.1 (p. 97) until you understand why you were wrong.
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
    for (decltype(size) index = 0; index < size; ++index) {
      // Print each element with its index in format [index]:value
      std::cout << '[' << index << "]:" << vec[index] << ' ';
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
 * size: 10, value: [0]:0 [1]:0 [2]:0 [3]:0 [4]:0 [5]:0 [6]:0 [7]:0 [8]:0 [9]:0
 * size: 10, value: [0]:42 [1]:42 [2]:42 [3]:42 [4]:42 [5]:42 [6]:42 [7]:42 [8]:42 [9]:42
 * size: 1, value: [0]:10
 * size: 2, value: [0]:10 [1]:42
 * size: 10, value: [0]: [1]: [2]: [3]: [4]: [5]: [6]: [7]: [8]: [9]:
 * size: 10, value: [0]:hi [1]:hi [2]:hi [3]:hi [4]:hi [5]:hi [6]:hi [7]:hi [8]:hi [9]:hi
 */