/*
 * Exercise 7.17: What, if any, are the differences between using class or
 * struct?
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/*
 * Struct example:
 * - Members are public by default
 * - Typically used for passive data structures
 */
struct Person {  // Default inheritance: public
  // Public by default
  std::string name_;
  std::string address_;

  // Can have constructors and methods
  void Print() const { std::cout << name_ << ", " << address_ << '\n'; }
};

/*
 * Class example:
 * - Members are private by default
 * - Typically used for active objects with encapsulation
 */
class Account {  // Default inheritance: private
  // Private by default
  std::string owner_;
  double balance_;

 public:
  // Explicit public interface
  explicit Account(const std::string& name, double initial)
      : owner_(name), balance_(initial) {}

  void Deposit(double amount) { balance_ += amount; }

  void Print() const {
    std::cout << owner_ << "'s balance: " << balance_ << '\n';
  }
};

/*
 * Key technical differences:
 * 1. Default member access:
 *    - struct: public
 *    - class: private
 * 2. Default inheritance:
 *    - struct: public
 *    - class: private
 * 3. Cultural conventions differ
 */
int main() {
  // Struct usage - direct member access
  Person person;
  person.name_ = "Alice";
  person.address_ = "123 Main St";
  person.Print();

  // Class usage - interface access
  Account acct("Bob", 100.0);
  acct.Deposit(50.0);
  acct.Print();

  // acct.balance = 1000000; // Error: private member

  /*
   * When to use each:
   * - Use struct for passive data aggregates
   * - Use class for encapsulated objects
   * - Be consistent within a codebase
   */

  return 0;
}

/* $ g++ -o main chapter-07/exercise-17.cc && ./main
 * Alice, 123 Main St
 * Bob's balance: 150
 */
