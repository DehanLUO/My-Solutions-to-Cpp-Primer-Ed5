/*
 * Exercise 12.5: We did not make the constructor that takes an initializer_list
 * explicit (§ 7.5.4, p. 296). Discuss the pros and cons of this design choice.
 */

#include <memory>     // std::shared_ptr
#include <stdexcept>  // std::out_of_range
#include <string>     // std::string
#include <vector>     // std::vector

class StrBlob {
 public:
  typedef std::vector<std::string>::size_type size_type;

  StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

  /**
   * @brief Non-explicit constructor from initializer_list
   *
   * Design choice discussion:
   * - Allows implicit conversion from braced-init-list
   *   StrBlob blob = {"apple", "banana", "cherry"};
   * - Enables convenient initialization syntax
   * - But may lead to unintended conversions
   */
  explicit StrBlob(std::initializer_list<std::string> il)
      : data(std::make_shared<std::vector<std::string>>(il)) {}

  size_type size() const { return data->size(); }

  bool empty() const { return data->empty(); }

  // add and remove elements
  void push_back(const std::string& t) { data->push_back(t); }
  void pop_back() { data->pop_back(); }

  // element access
  std::string& front() {
    check(0, "front on empty StrBlob");
    return data->front();
  };
  std::string& back() {
    check(0, "back on empty StrBlob");
    return data->back();
  }

 private:
  std::shared_ptr<std::vector<std::string>> data;
  void check(size_type i, const std::string& msg) const {
    if (i >= data->size()) throw std::out_of_range(msg);
  }
};