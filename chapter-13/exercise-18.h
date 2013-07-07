/*
 * Exercise 13.18: Define an Employee class that contains an employee name and a
 * unique employee identifier. Give the class a default constructor and a
 * constructor that takes a string representing the employee’s name. Each
 * constructor should generate a unique ID by incrementing a static data member.
 */

#ifndef CHAPTER_13_EXERCISE_18_H_
#define CHAPTER_13_EXERCISE_18_H_

#include <cstdint>    // uint16_t
#include <iostream>   // std::ostream, std::cout
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string

/**
 * @class Employee
 * @brief Represents an employee with a unique identifier and name.
 *
 * This class maintains a static counter to generate unique IDs for each
 * employee. The IDs are assigned sequentially starting from 1 and cannot exceed
 * the maximum value of uint16_t (65,535). Throws std::runtime_error if maximum
 * employee count is reached.
 */
class Employee {
  // Friend declaration for output stream operator
  friend std::ostream& operator<<(std::ostream&, const Employee&);

 public:
  /**
   * @brief Default constructor.
   *
   * Creates an employee with an empty name and a unique ID.
   * @throws std::runtime_error if maximum employee count is reached.
   */
  Employee() : id_(GenerateId()) {}

  /**
   * @brief Parameterized constructor.
   * @param name The employee's name.
   *
   * Creates an employee with the given name and a unique ID.
   * @throws std::runtime_error if maximum employee count is reached.
   */
  Employee(const std::string& name) : id_(GenerateId()), name_(name) {}

  /**
   * @brief Default copy constructor.
   */
  Employee(const Employee&) = default;

  /**
   * @brief Default copy assignment.
   */
  Employee& operator=(const Employee&) = default;

  /**
   * @brief Default destructor.
   */
  ~Employee() = default;

  // Accessors

  /**
   * @brief Gets the employee's ID.
   * @return The employee's unique identifier.
   */
  uint16_t GetId() const { return id_; }

  /**
   * @brief Gets the employee's name.
   * @return Const reference to the employee's name.
   */
  const std::string& GetName() const { return name_; }

  // Mutator

  /**
   * @brief Sets the employee's name.
   * @param name The new name for the employee.
   */
  void SetName(const std::string& name) { name_ = name; }

 private:
  /**
   * @brief Generates a unique employee ID.
   * @return The next available employee ID.
   * @throws std::runtime_error if maximum employee count is reached.
   *
   * This static method maintains the sequence of employee IDs and ensures
   * no duplicates are generated. IDs start at 1 and increment by 1 for each
   * new employee.
   */
  static uint16_t GenerateId() {
    if (UINT16_MAX == next_id_) {
      throw std::runtime_error("Maximum employee count reached");
    }
    return next_id_++;
  }

 private:
  static uint16_t next_id_;  // Static counter for generating unique IDs
  uint16_t id_;              // The employee's unique identifier
  std::string name_;         // The employee's name
};

/**
 * @brief Overloaded output stream operator for Employee class.
 * @param ostream The output stream to write to.
 * @param employee The Employee object to output.
 * @return Reference to the output stream.
 *
 * Outputs employee information in the format:
 * Employee{id: <id>, name: <name>}
 */
std::ostream& operator<<(std::ostream& ostream, const Employee& employee) {
  ostream << "Employee{id: " << employee.id_ << ", name: " << employee.name_
          << "}";
  return ostream;
}

#endif  // CHAPTER_13_EXERCISE_18_H_
