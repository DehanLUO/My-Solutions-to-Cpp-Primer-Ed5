/*
 * Exercise 3.4: Write a program to read two strings and report whether the
 * strings are equal. If not, report which of the two is larger. Now, change the
 * program to report whether the strings have the same length, and if not,
 * report which is longer.
 */

#include <iostream>  // std::cin, std::cout
#include <string>    // std::string

int main() {
  using std::cin;
  using std::cout;
  using std::string;

  string user_input_a, user_input_b;
  cout << "Enter two strings:\n";
  cin >> user_input_a >> user_input_b;

  // Compare string equality and lexicographical order
  if (user_input_a == user_input_b) {
    cout << "The strings are equal.\n";
  } else if (user_input_a > user_input_b) {
    cout << "The first string is larger.\n";
  } else {
    cout << "The second string is larger.\n";
  }

  // Compare string lengths
  const auto size_a = user_input_a.size();
  const auto size_b = user_input_b.size();
  if (size_a == size_b) {
    cout << "The strings have the same length.\n";
  } else if (size_a > size_b) {
    cout << "The first string is longer.\n";
  } else {
    cout << "The second string is longer.\n";
  }

  return 0;
}

/*
 * $ g++ -o main exercise03-04.cc && ./main
 * Enter two strings:
 * tech otakus
 * The first string is larger.
 * The second string is longer.
 */