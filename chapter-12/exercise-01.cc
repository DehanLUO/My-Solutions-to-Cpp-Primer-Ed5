/*
 * Exercise 12.1: How many elements do b1 and b2 have at the end of this code?
 *     StrBlob b1;
 *     {
 *       StrBlob b2 = {"a", "an", "the"};
 *       b1 = b2;
 *       b2.push_back("about");
 *     }
 */

#include <initializer_list>  // std::initializer_list
#include <iostream>          // std::cout
#include <memory>            // std::shared_ptr
#include <stdexcept>         // std::out_of_range
#include <string>            // std::string
#include <vector>            // std::vector

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
  // thows msg if data[i] isn't valid
  void check(size_type i, const std::string& msg) const {
    if (i >= data->size()) throw std::out_of_range(msg);
  }
};

/**
 * @brief Demonstrates StrBlob behavior with shared ownership
 */
void AnalyzeStrBlobBehavior() {
  StrBlob b1;
  size_t b1_size_after_scope;

  {
    StrBlob b2 = {"a", "an", "the"};  // b2 creates a vector with 3 elements
    b1 = b2;                // b1 and b2 share ownership after assignment
    b2.push_back("about");  // ush_back affects both b1 and b2
    b1_size_after_scope = b1.size();  // Value: 4
  }

  /*
   * Key observations:
   * - b1 retains the vector after b2 goes out of scope
   * - Reference count drops to 1 when b2 is destroyed
   * - Vector contents persist through b1
   */
  std::cout << "b1 size after scope: " << b1.size() << '\n';  // Outputs 4
  std::cout << "b1 elements: ";
  while (!b1.empty()) {
    std::cout << b1.back() << " ";
    b1.pop_back();
  }
  std::cout << '\n';
}

int main() {
  AnalyzeStrBlobBehavior();

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-01.cc && ./main
 * b1 size after scope: 4
 * b1 elements: about the an a
 */
