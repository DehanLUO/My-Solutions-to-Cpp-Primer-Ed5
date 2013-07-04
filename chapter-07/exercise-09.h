/*
 * Exercise 7.9: Add operations to read and print Person objects to the code you
 * wrote for the exercises in § 7.1.2 (p. 260).
 */

#ifndef CHAPTER_07_EXERCISE_09_H_
#define CHAPTER_07_EXERCISE_09_H_

#include <iostream>  // std::istream, std::ostream
#include <string>    // std::string

struct Person {
  std::string name;
  std::string address;

  /**
   * @brief Retrieves the person's name
   * @return Copy of the name string
   * @note Marked const as it doesn't modify object state
   */
  std::string GetName() const { return name; }

  /**
   * @brief Retrieves the person's address
   * @return Copy of the address string
   * @note Marked const as it doesn't modify object state
   */
  std::string GetAddress() const { return address; }

  /**
   * @brief Reads person data from input stream
   * @param input_stream Source stream for data
   * @param person Target Person object to populate
   * @return Reference to modified input stream
   * @note Modifies Person parameter (non-const reference)
   */
  static std::istream& Read(std::istream& input_stream, Person& person) {
    person.name.clear();
    person.address.clear();

    return input_stream >> person.name >> person.address;
  }

  /**
   * @brief Writes person data to output stream
   * @param output_stream Destination stream for data
   * @param person Source Person object to display
   * @return Reference to modified output stream
   * @note Does not modify Person (const reference)
   */
  std::ostream& Print(std::ostream& output_stream, const Person& person) const {
    return output_stream << person.name << ' ' << person.address;
  }
};

#endif  // CHAPTER_07_EXERCISE_09_H_
