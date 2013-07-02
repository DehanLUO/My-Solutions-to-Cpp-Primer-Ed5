/*
 * Exercise 3.26: In the binary search program on page 112, why did we write mid
 * = beg + (end - beg) / 2; instead of mid = (beg + end) /2;?
 */

#include <iostream>  // std::cout
#include <string>    // std::string
#include <vector>    // std::vector

int main() {
  std::vector<std::string> text = {"apple",   //
                                   "banana",  //
                                   "grapde",  //
                                   "orange",  //
                                   "pear"};

  std::string sought = "orange";  // Target to search for

  /*
   * 1. Iterator arithmetic rules: In c++, `beg` and `end` are iteraotors, not
   * numbers. You cannot add two iterators together like `(beg + end)`. The
   * expression `(end - beg)` is valid --- it returns the number of elements
   * between them --- and that value can be divided by 2 and added to `beg`.
   *
   * 2. Avoiding integer overflow: Even if `beg` and `end` were integer indices,
   * computing `(beg + end)` directly could overflow if both values are large.
   * The expression `beg + (end - beg) / 2` is mathematically equivalent but
   * safer, since it reduces the size of intemediate values.
   */

  // beg and end will denote the range we are searching
  auto beg = text.begin();
  auto end = text.end();
  auto mid = text.begin() + (end - beg) / 2;  // original midpoint

  // while there are still elements to look at and we have not yet found sought
  while (mid != end && *mid != sought) {
    if (sought < *mid)  // is the element we want in the first half?
      end = mid;        // if so, adjust the range to ignore the second half
    else                // the element we want is in the second half
      beg = mid + 1;    // start looking with the element just after mid
    mid = beg + (end - beg) / 2;  // new midpoint
  }

  // Output result
  if (mid != end) {
    std::cout << "Found '" << sought << "' at position " << (mid - text.begin())
              << '\n';
  } else {
    std::cout << "'" << sought << "' not found in the vector.\n";
  }

  return 0;
}

/*
 * $  g++ -o main exercise-26.cc && ./main
 * Found 'orange' at position 3
 */