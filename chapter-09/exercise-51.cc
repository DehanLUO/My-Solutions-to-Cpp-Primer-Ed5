/*
 * Exercise 9.51: Write a class that has three unsigned members representing
 * year, month, and day. Write a constructor that takes a string representing a
 * date. Your constructor should handle a variety of date formats, such as
 * January 1, 1900, 1/1/1900, Jan 1, 1900, and so on.
 */

#include <cctype>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class Date {
 public:
  Date(const std::string& date_str) {
    if (!ParseDate(date_str)) {
      throw std::invalid_argument("Invalid date format: " + date_str);
    }
  }

  unsigned GetYear() const { return year_; }
  unsigned GetMonth() const { return month_; }
  unsigned GetDay() const { return day_; }

  void Print() const {
    std::cout << year_ << "-" << month_ << "-" << day_ << '\n';
  }

 private:
  unsigned year_;
  unsigned month_;
  unsigned day_;

  static const std::map<std::string, unsigned> month_map;

  bool ParseDate(const std::string& date_str) {
    // Try different formats
    return ParseFormat1(date_str) ||  // January 1, 1900
           ParseFormat2(date_str) ||  // Jan 1, 1900
           ParseFormat3(date_str) ||  // 1/1/1900
           ParseFormat4(date_str);    // 1-1-1900
  }

  bool ParseFormat1(const std::string& date_str) {
    // Format: January 1, 1900
    size_t space1 = date_str.find(' ');
    if (space1 == std::string::npos) return false;

    size_t comma = date_str.find(',', space1 + 1);
    if (comma == std::string::npos) return false;

    std::string month_str = date_str.substr(0, space1);
    std::string day_str = date_str.substr(space1 + 1, comma - space1 - 1);
    std::string year_str = date_str.substr(comma + 2);

    return AssignDate(month_str, day_str, year_str);
  }

  bool ParseFormat2(const std::string& date_str) {
    // Format: Jan 1, 1900
    size_t space1 = date_str.find(' ');
    if (space1 == std::string::npos || space1 != 3) return false;

    size_t comma = date_str.find(',', space1 + 1);
    if (comma == std::string::npos) return false;

    std::string month_str = date_str.substr(0, space1);
    std::string day_str = date_str.substr(space1 + 1, comma - space1 - 1);
    std::string year_str = date_str.substr(comma + 2);

    return AssignDate(month_str, day_str, year_str);
  }

  bool ParseFormat3(const std::string& date_str) {
    // Format: 1/1/1900
    size_t slash1 = date_str.find('/');
    if (slash1 == std::string::npos) return false;

    size_t slash2 = date_str.find('/', slash1 + 1);
    if (slash2 == std::string::npos) return false;

    std::string month_str = date_str.substr(0, slash1);
    std::string day_str = date_str.substr(slash1 + 1, slash2 - slash1 - 1);
    std::string year_str = date_str.substr(slash2 + 1);

    return AssignDate(month_str, day_str, year_str);
  }

  bool ParseFormat4(const std::string& date_str) {
    // Format: 1-1-1900
    size_t dash1 = date_str.find('-');
    if (dash1 == std::string::npos) return false;

    size_t dash2 = date_str.find('-', dash1 + 1);
    if (dash2 == std::string::npos) return false;

    std::string month_str = date_str.substr(0, dash1);
    std::string day_str = date_str.substr(dash1 + 1, dash2 - dash1 - 1);
    std::string year_str = date_str.substr(dash2 + 1);

    return AssignDate(month_str, day_str, year_str);
  }

  bool AssignDate(const std::string& month_str, const std::string& day_str,
                  const std::string& year_str) {
    try {
      // Parse month
      if (isalpha(month_str[0])) {
        // Month is alphabetic (January or Jan)
        std::string month_lower;
        for (char c : month_str) {
          month_lower += tolower(c);
        }
        // Handle both full and abbreviated month names
        auto it = month_map.find(month_lower.substr(0, 3));
        if (it == month_map.end()) return false;
        month_ = it->second;
      } else {
        // Month is numeric
        month_ = std::stoul(month_str);
        if (month_ < 1 || month_ > 12) return false;
      }

      // Parse day
      day_ = std::stoul(day_str);
      if (day_ < 1 || day_ > 31) return false;

      // Parse year
      year_ = std::stoul(year_str);
      if (year_ < 1900 || year_ > 2100) return false;  // Arbitrary range

      return true;
    } catch (...) {
      return false;
    }
  }
};

// Initialize static month map
const std::map<std::string, unsigned> Date::month_map = {
    {"jan", 1}, {"feb", 2}, {"mar", 3}, {"apr", 4},  {"may", 5},  {"jun", 6},
    {"jul", 7}, {"aug", 8}, {"sep", 9}, {"oct", 10}, {"nov", 11}, {"dec", 12}};

int main() {
  // Test different date formats
  std::vector<std::string> test_dates = {
      "January 1, 1900",   "Jan 1, 1900",  "1/1/1900",   "1-1-1900",
      "December 31, 2099", "Dec 31, 2099", "12/31/2099", "12-31-2099"};

  for (const auto& date_str : test_dates) {
    try {
      Date date(date_str);
      std::cout << date_str << " -> ";
      date.Print();
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << '\n';
    }
  }

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-51.cc && ./main
 * January 1, 1900 -> 1900-1-1
 * Jan 1, 1900 -> 1900-1-1
 * 1/1/1900 -> 1900-1-1
 * 1-1-1900 -> 1900-1-1
 * December 31, 2099 -> 2099-12-31
 * Dec 31, 2099 -> 2099-12-31
 * 12/31/2099 -> 2099-12-31
 * 12-31-2099 -> 2099-12-31
 */
