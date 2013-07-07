/*
 * Exercise 12.4: In our check function we didn’t check whether i was greater
 * than zero. Why is it okay to omit that check?
 */

#include <memory>     // std::shared_ptr
#include <stdexcept>  // std::out_of_range
#include <string>     // std::string
#include <vector>     // std::vector

class StrBlob {
 public:
  typedef std::vector<std::string>::size_type size_type;

  StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

  StrBlob(std::initializer_list<std::string> il)
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

  /**
   * @brief Validates index access to the StrBlob
   * @param i Index to check
   * @param msg Error message for out_of_range exception
   * @throws std::out_of_range if index is invalid
   *
   * Why we don't check i > 0:
   * 1. size_type is unsigned (always >= 0)
   * 2. Only need to verify upper bound
   * 3. front()/back() pass 0 which is always valid for non-empty vectors
   */
  void check(size_type i, const std::string& msg) const {
    if (i >= data->size()) throw std::out_of_range(msg);
  }
};
