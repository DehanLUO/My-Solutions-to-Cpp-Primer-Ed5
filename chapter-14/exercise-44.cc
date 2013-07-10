/*
 * Exercise 14.44: Write your own version of a simple desk calculator that can
 * handle binary operations.
 */

#include <functional>  // std::function, std::plus, std::minus, std::multiplies, std::divides, std::modulus
#include <iostream>    // std::cin, std::cout
#include <map>         // std::map
#include <sstream>     // std::istringstream
#include <stdexcept>   // std::out_of_range, std::invalid_argument
#include <string>      // std::string

class DeskCalculator {
 public:
  /**
   * @brief Constructs a DeskCalculator with predefined operations
   */
  DeskCalculator() {
    operations_ = {{"+", std::plus<int>()},
                   {"-", std::minus<int>()},
                   {"*", std::multiplies<int>()},
                   {"/",
                    [](int dividend, int divisor) {
                      if (0 == divisor)
                        throw std::invalid_argument("Division by zero");
                      return dividend / divisor;
                    }},
                   {"%", [](int dividend, int modulus) {
                      if (0 == modulus)
                        throw std::invalid_argument("Modulus by zero");
                      return dividend % modulus;
                    }}};
  }

  /**
   * @brief Performs calculation based on operator and operands
   * @param left Left operand
   * @param oper Operator string
   * @param right Right operand
   * @return int Result of the operation
   * @throw std::out_of_range if operator is not supported
   * @throw std::invalid_argument for division by zero
   */
  int Calculate(int left, const std::string& oper, int right) const {
    /*
     * Check if the requested operation exists in the operations map.
     * The at() method provides bounds checking and throws out_of_range
     * for invalid operators.
     */
    auto iter = operations_.find(oper);
    if (operations_.end() == iter)
      throw std::out_of_range("Unsupported operator: " + oper);

    /*
     * Execute the operation using the stored function object.
     * Division and modulus operations include zero checking through
     * their lambda implementations.
     */
    return iter->second(left, right);
  }

  /**
   * @brief Gets the list of supported operators
   * @return std::string Comma-separated list of operators
   */
  std::string GetSupportedOperators() const {
    std::string result;
    for (const auto& pair : operations_) {
      if (!result.empty()) result += ", ";
      result += pair.first;
    }
    return result;
  }

 private:
  std::map<std::string, std::function<int(int, int)>> operations_;
};

int main() {
  DeskCalculator calculator;

  std::cout << "Simple Desk Calculator\n";
  std::cout << "Support operators: " << calculator.GetSupportedOperators()
            << '\n';
  std::cout << "Enter expressions in format: number operator number\n";

  std::string input;
  std::getline(std::cin, input);
  try {
    std::istringstream iss(input);
    int left{};
    int right{};
    std::string oper;

    if (!(iss >> left >> oper >> right))
      throw std::invalid_argument("invalid input format.");

    int result = calculator.Calculate(left, oper, right);
    std::cout << "Result: " << result << '\n';
  } catch (const std::out_of_range& e) {
    std::cerr << "Error: " << e.what() << '\n';
  } catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << '\n';
  } catch (const std::exception& e) {
    std::cerr << "Unexpected error: " << e.what() << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-44.cc && ./main
 * Simple Desk Calculator
 * Support operators: %, *, +, -, /
 * Enter expressions in format: number operator number
 * 5 * 3
 * Result: 15
 */
