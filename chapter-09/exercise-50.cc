/*
 * Exercise 9.50: Write a program to process a vector<string>s whose elements
 * represent integral values. Produce the sum of all the elements in that
 * vector. Change the program so that it sums of strings that represent
 * floating-point values.
 */

#include <iostream>  // std::cout
#include <string>    // std::string
#include <vector>    // std::vector

// Sum integral values represented as strings
int SumIntegralStrings(const std::vector<std::string>& strs) {
  int sum = 0;
  for (const auto& s : strs) {
    try {
      sum += std::stoi(s);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Warning: '" << s << "' is not a valid integer\n";
    } catch (const std::out_of_range& e) {
      std::cerr << "Warning: '" << s << "' is out of integer range\n";
    }
  }
  return sum;
}

// Sum floating-point values represented as strings
double SumFloatingStrings(const std::vector<std::string>& strs) {
  double sum = 0.0;
  for (const auto& s : strs) {
    try {
      sum += std::stod(s);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Warning: '" << s
                << "' is not a valid floating-point number\n";
    } catch (const std::out_of_range& e) {
      std::cerr << "Warning: '" << s << "' is out of floating-point range\n";
    }
  }
  return sum;
}

int main() {
  // Test with integral values
  std::vector<std::string> int_strs = {"1", "2", "3", "4", "5"};
  std::cout << "Sum of integers: " << SumIntegralStrings(int_strs) << "\n";

  // Test with floating-point values
  std::vector<std::string> float_strs = {"1.1", "2.2", "3.3", "4.4", "5.5"};
  std::cout << "Sum of floats: " << SumFloatingStrings(float_strs) << "\n";

  // Test with mixed values (including invalid ones)
  std::vector<std::string> mixed_strs = {"10", "3.14", "hello", "42", "2.718"};
  std::cout << "Sum of mixed as integers: " << SumIntegralStrings(mixed_strs)
            << "\n";
  std::cout << "Sum of mixed as floats: " << SumFloatingStrings(mixed_strs)
            << "\n";

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-50.cc && ./main
 * Sum of integers: 15
 * Sum of floats: 16.5
 * Sum of mixed as integers: Warning: 'hello' is not a valid integer
 * 57
 * Sum of mixed as floats: Warning: 'hello' is not a valid floating-point number
 * 57.858
 */
