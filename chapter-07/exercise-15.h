/*
 * Exercise 7.15: Add appropriate constructors to your Person class.
 */

#ifndef CHAPTER_07_EXERCISE_15_H_
#define CHAPTER_07_EXERCISE_15_H_

#include <iostream>  // std::istream, std::ostream
#include <string>    // std::string

struct Person {
  std::string name;
  std::string address;

  /*
   * Constructor suite providing complete initialization options:
   * 1. Default construction
   * 2. Name-only initialization
   * 3. Complete manual initialization
   * 4. Stream-based initialization
   * 5. Copy construction
   */

  /**
   * @brief Default constructor
   * @note Creates empty Person object
   */
  Person() = default;

  /**
   * @brief Copy constructor
   * @param other Source Person to copy from
   */
  Person(const Person& other) = default;

  /**
   * @brief Constructs with name only
   * @param name Individual's complete name
   * @note Explicit to prevent implicit conversions
   */
  explicit Person(const std::string& name) : Person(name, "") {}

  /**
   * @brief Complete manual initialization
   * @param name Individual's complete name
   * @param address Complete mailing address
   * @note Explicit to prevent implicit conversions
   */
  explicit Person(const std::string& name, const std::string& address)
      : name(name), address(address) {}

  /**
   * @brief Stream initialization constructor
   * @param input_stream Input stream to read from
   * @note Explicit to prevent implicit conversions
   */
  explicit Person(std::istream& input_stream) { Read(input_stream, *this); }

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

#endif  // CHAPTER_07_EXERCISE_15_H_
