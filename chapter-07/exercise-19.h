/*
 * Exercise 7.19: Indicate which members of your Person class you would declare
 * as public and which you would declare as private. Explain your choice.
 */

#ifndef CHAPTER_07_EXERCISE_19_H_
#define CHAPTER_07_EXERCISE_19_H_

#include <iostream>  // std::istream, std::ostream
#include <string>    // std::string

class Person {
 private:
  std::string name_;
  std::string address_;

 public:  // safe operations exposed to users
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
      : name_(name), address_(address) {}

  /**
   * @brief Stream initialization constructor
   * @param input_stream Input stream to read from
   * @note Explicit to prevent implicit conversions
   */
  explicit Person(std::istream& input_stream) { Read(input_stream, *this); }

  /**
   * @brief Retrieves the person's name
   * @return Const reference of the name string
   * @note Marked const as it doesn't modify object state
   */
  const std::string& GetName() const { return name_; }

  /**
   * @brief Retrieves the person's address
   * @return Const reference of the address string
   * @note Marked const as it doesn't modify object state
   */
  const std::string& GetAddress() const { return address_; }

  /**
   * @brief Reads person data from input stream
   * @param input_stream Source stream for data
   * @param person Target Person object to populate
   * @return Reference to modified input stream
   * @note Modifies Person parameter (non-const reference)
   */
  static std::istream& Read(std::istream& input_stream, Person& person) {
    person.name_.clear();
    person.address_.clear();

    return input_stream >> person.name_ >> person.address_;
  }

  /**
   * @brief Writes person data to output stream
   * @param output_stream Destination stream for data
   * @param person Source Person object to display
   * @return Reference to modified output stream
   * @note Does not modify Person (const reference)
   */
  static std::ostream& Print(std::ostream& output_stream,
                             const Person& person) {
    return output_stream << person.name_ << ' ' << person.address_;
  }
};

/*
 * Private members:
 * `name_` and `address_` are private members. Direct modification could lead to
 * invalid states.
 *
 * Public members:
 * - Constructors. Needed for object creation. Explicit to prevent unintended
 *   conversions.
 * - Accessors. Safe read-only access to data. Return const references for
 *   efficiency.
 * - Mutators. Controlled modification with validation. Can add
 *   longging/notification later.
 * - I/O operations. Essential clas functionality. Static for clearer semantics.
 */

#endif  // CHAPTER_07_EXERCISE_19_H_
