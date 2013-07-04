/*
 * Exercise 7.57: Write your own version of the Account class.
 */

/*
 * Exercise 7.57 Solution
 * Account class implementation with static members
 * Standard: ISO/IEC 14882:2017 §11.4.8, §11.4.9
 */

#include <iostream>
#include <string>

/**
 * @brief Bank account class with static interest rate
 */
class Account {
 public:
  /**
   * @brief Constructs an Account with owner and initial balance
   * @param owner Account holder name
   * @param initial_balance Starting balance
   */
  explicit Account(const std::string& owner, double initial_balance = 0.0)
      : owner_(owner), balance_(initial_balance) {}

  /**
   * @brief Deposits specified amount
   * @param amount Positive deposit value
   */
  void Deposit(double amount) { balance_ += amount; }

  /**
   * @brief Withdraws specified amount
   * @param amount Positive withdrawal value
   * @return true if withdrawal successful
   */
  bool Withdraw(double amount) {
    if (amount > balance_) return false;
    balance_ -= amount;
    return true;
  }

  /**
   * @brief Calculates interest with current rate
   * @return Interest amount
   */
  double CalculateInterest() const { return balance_ * interest_rate_; }

  /**
   * @brief Gets current balance
   * @return Account balance
   */
  double GetBalance() const { return balance_; }

  /**
   * @brief Gets account owner
   * @return Owner name
   */
  std::string GetOwner() const { return owner_; }

  // Static member functions
  /**
   * @brief Sets new interest rate
   * @param new_rate New rate (e.g., 0.05 for 5%)
   */
  static void SetInterestRate(double new_rate) { interest_rate_ = new_rate; }

  /**
   * @brief Gets current interest rate
   * @return Current rate
   */
  static double GetInterestRate() { return interest_rate_; }

 private:
  std::string owner_;  // Account holder name
  double balance_;     // Current balance

  // Static data member - shared by all accounts
  static double interest_rate_;  // Current interest rate
};

// Definition of static member
double Account::interest_rate_ = 0.02;  // Default 2% interest

int main() {
  Account alice("Alice", 1000.0);
  Account bob("Bob", 500.0);

  // All accounts share the same interest rate
  Account::SetInterestRate(0.03);  // Set to 3%

  alice.Deposit(200.0);
  bob.Withdraw(100.0);

  std::cout << "Alice's balance: " << alice.GetBalance()
            << ", interest: " << alice.CalculateInterest() << '\n';
  std::cout << "Bob's balance: " << bob.GetBalance()
            << ", interest: " << bob.CalculateInterest() << '\n';

  return 0;
}

/* $ g++ -o main chapter-07/exercise-57.cc && ./main
 * Alice's balance: 1200, interest: 36
 * Bob's balance: 400, interest: 12
 */
