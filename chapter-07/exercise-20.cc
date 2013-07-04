/*
 * Exercise 7.20: When are friends useful? Discuss the pros and cons of using
 * friends.
 */

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

  friend class PrivacyAuditor;
};

class PrivacyAuditor {
 public:
  /**
   * @brief Audit address access log
   * @param person Person object to audit
   * @note Can access private address_ member due to friend status
   */
  static void PrintAddress(const Person& person) {
    std::cout << "[Audit] Address accessed: " << person.address_ << '\n';
  }
};

void PublicInfo(const Person& person) {
  std::cout << "Public name: " << person.GetName() << '\n';
}

int main() {
  Person alice("Alice", "123 Secret Lane");

  // Normal public interface usage
  PublicInfo(alice);

  // Privileged friend access
  PrivacyAuditor::PrintAddress(alice);

  return 0;
}

/**
 * When Friends Are Useful:
 * 1. Operator Overloading (<<, >>)
 * 2. Factory Patterns (private constructor access)
 * 3. Tightly Coupled Components (e.g., PrivacyAuditor)
 * 4. Test Classes (white-box testing)
 *
 * Advantages in This Example:
 * - Allows PrivacyAuditor to verify addresses without exposing them publicly
 * - Maintains normal encapsulation for all other code
 * - Explicitly documents special relationship
 *
 * Potential Drawbacks:
 * - Increases coupling between Person and PrivacyAuditor
 * - Overuse can weaken encapsulation
 * - Requires careful documentation
 *
 * Best Practices Demonstrated:
 * - Limited to one clearly named friend class
 * - All access is read-only
 * - Well-documented purpose
 */

/* $ g++ -o main chapter-07/exercise-20.cc && ./main
 * Public name: Alice
 * [Audit] Address accessed: 123 Secret Lane
 */