/*
 * Exercise 7.18: What is encapsulation? Why is it useful?
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/*
 * Encapsulated BankAccount class
 * Demonstrates proper data hiding and interface control
 */
class BankAccount {
 private:  // Implementation details hidden
  std::string owner_name_;
  double balance_;
  double interest_rate_;

  // Private helper method
  void ApplyInterest() { balance_ += balance_ * interest_rate_; }

 public:  // Public interface exposed
  /**
   * @brief Constructs a new BankAccount
   * @param name Account owner name
   * @param initial Initial deposit amount
   * @param rate Annual interest rate (0-1)
   */
  BankAccount(const std::string& name, double initial, double rate)
      : owner_name_(name), balance_(initial), interest_rate_(rate) {
    if (initial < 0) balance_ = 0;
    if (rate < 0 || rate > 1) interest_rate_ = 0.01;
  }

  /**
   * @brief Deposits money into account
   * @param amount Positive deposit amount
   * @return New balance
   */
  double Deposit(double amount) {
    if (amount > 0) balance_ += amount;
    return balance_;
  }

  /**
   * @brief Withdraws money from account
   * @param amount Positive withdrawal amount
   * @return Actual amount withdrawn
   */
  double Withdraw(double amount) {
    if (amount <= 0) return 0;
    double actual = (amount > balance_) ? balance_ : amount;
    balance_ -= actual;
    return actual;
  }

  /**
   * @brief Applies annual interest
   * @return New balance after interest
   */
  double ApplyAnnualInterest() {
    ApplyInterest();
    return balance_;
  }

  /**
   * @brief Gets current balance
   * @return Current account balance
   */
  double GetBalance() const { return balance_; }

  /**
   * @brief Gets owner name
   * @return Account owner name
   */
  std::string GetOwnerName() const { return owner_name_; }
};

/*
 * Unencapsulated alternative - exposes all internals
 */
struct RawAccount {
  std::string owner_name;
  double balance;
  double interest_rate;
};

int main() {
  // Using encapsulated version
  BankAccount my_account("Alice", 1000.0, 0.05);
  my_account.Deposit(500.0);
  my_account.Withdraw(200.0);
  my_account.ApplyAnnualInterest();
  std::cout << my_account.GetOwnerName() << "'s balance: $"
            << my_account.GetBalance() << "\n";

  // Using unencapsulated version - dangerous!
  RawAccount raw_account;
  raw_account.balance = 1000.0;
  raw_account.interest_rate = 0.05;
  raw_account.balance = -5000.0;  // Invalid state possible
  raw_account.balance *= 1 + raw_account.interest_rate;  // Manual operation

  /*
   * Key benefits of encapsulation:
   * 1. Prevents invalid states (negative balance)
   * 2. Hides implementation details (interest calculation)
   * 3. Allows internal changes without breaking clients
   * 4. Provides controlled access through methods
   */
  return 0;
}
/* $ g++ -o main chapter-07/exercise-18.cc && ./main
 * Alice's balance: $1365
 */
