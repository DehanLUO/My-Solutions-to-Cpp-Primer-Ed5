/*
 * Exercise 8.11: The program in this section defined its istringstream object
 * inside the outer while loop. What changes would you need to make if record
 * were defined outside that loop? Rewrite the program, moving the definition of
 * record outside the while, and see whether you thought of all the changes that
 * are needed.
 */

#include <iostream>  // std::cin
#include <sstream>   // std::istringstream
#include <string>    // std::string
#include <vector>    // std::vector

// members are public by default; see § 7.2 (p. 268)
struct PersonInfo {
  std::string name;
  std::vector<std::string> phones;
};

int main() {
  std::string line, word;  // will hold a line and word from input, respectively
  std::vector<PersonInfo> people;  // will hold all the records from the input
  // read the input a line at a time until cin hits end-of-file (or another
  // error)

  std::istringstream record(line);  // Moved outside the loop

  while (std::getline(std::cin, line)) {
    PersonInfo info;  // create an object to hold this record's data

    // Reset and reuse the string stream
    record.clear();    // Clear any error states
    record.str(line);  // Set new content

    record >> info.name;            // read the name
    while (record >> word) {        // read the phone numbers
      info.phones.push_back(word);  // and store them
    }
    people.push_back(info);  // append this record to people
  }
  return 0;
}
