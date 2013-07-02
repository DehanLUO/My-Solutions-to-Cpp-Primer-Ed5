/*
 * Exercise 3.5: Write a program to read strings from the standard input,
 * concatenating what is read into one large string. Print the concatenated
 * string. Next, change the program to separate adjacent input strings by a
 * space.
 */

#include <iostream>  // std::cin, std::cout
#include <string>    // std::string

int main() {
  using std::cin;
  using std::cout;
  using std::string;

  string input;
  string concatenated;
  string separated;
  cout << "Enter strings (ctrl+D to end):\n";

  // Read input until EOF
  while (cin >> input) {
    concatenated += input;
    separated += input + ' ';
  }

  cout << "Concatenated string: " << concatenated << '\n';

  if (!separated.empty()) {
    separated.pop_back();  // Remove the last space
  }
  cout << "Space-separated concatenation: " << separated << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise-05.cc && ./main
 * Enter strings (ctrl+D to end):
 * The
 * quick
 * brown
 * fox
 * jumps
 * over
 * the
 * lazy
 * dog.
 * Concatenated string: Thequickbrownfoxjumpsoverthelazydog.
 * Space-separated concatenation: The quick brown fox jumps over the lazy dog.
 */