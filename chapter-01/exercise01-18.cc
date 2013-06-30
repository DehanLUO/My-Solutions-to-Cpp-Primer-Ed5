/*
 * Exercise 1.18: Compile and run the program from this section giving it only
 * equal values as input. Run it again giving it values in which no number is
 * repeated.
 */

#include <iostream>  // std::cin, std::cout

int main() {
  // curr_val is the number we’re counting; we’ll read new values into val
  int curr_val = 0;
  int val = 0;
  // read first number and ensure that we have data to process
  if (std::cin >> curr_val) {
    int cnt = 1;  // store the count for the current value we’re processing
    while (std::cin >> val) {  // read the remaining numbers
      if (val == curr_val)     // if the values are the same
        ++cnt;                 // add 1 to cnt
      else {  // otherwise, print the count for the previous value
        std::cout << curr_val << " occurs " << cnt << " times" << '\n';
        curr_val = val;  // remember the new value
        cnt = 1;         // reset the counter
      }
    }  // while loop ends here
    // remember to print the count for the last value in the file
    std::cout << curr_val << " occurs " << cnt << " times" << '\n';
  }  // outermost if statement ends here
  return 0;
}

/*
 * $ g++ -o main exercise01-18.cc && ./main
 * 9527 9527 9527 9527 9527
 * 9527 occurs 5 times
 * $ ./main
 * -1 0 1 42 1729
 * -1 occurs 1 times
 * 0 occurs 1 times
 * 1 occurs 1 times
 * 42 occurs 1 times
 * 1729 occurs 1 times
 */