/*
 * Exercise 5.13: Each of the programs in the highlighted text on page 184
 * contains a common programming error. Identify and correct each error.
 */

#include <vector>  // std::vector

// Helper declarations (simulated for compilation)
char NextText() { return 'a'; }
unsigned SomeValue() { return 1; }
int GetValue() { return 2; }
int GetNum() { return 3; }
unsigned GetBufCnt() { return 4; }
std::vector<int> ivec(2);  // Required for part (b)

int main() {
  // --- Part (a) Correction ---
  unsigned a_cnt = 0, e_cnt = 0, i_o_u_cnt = 0;
  char ch = NextText();
  switch (ch) {
    case 'a':
      a_cnt++;
      break;  // Missing break statement
    case 'e':
      e_cnt++;
      break;  // Missing break statement
    default:
      i_o_u_cnt++;
  }

  // --- Part (b) Correction ---
  unsigned index = SomeValue();
  int ix;  // Declaration moved outside switch
  switch (index) {
    case 1:
      ix = GetValue();  // Initialization only in case 1
      ivec[ix] = index;
      break;
    default:
      ix = ivec.size() - 1;
      ivec[ix] = index;
  }

  // --- Part (c) Correction ---
  unsigned even_cnt = 0, odd_cnt = 0;
  int digit = GetNum() % 10;
  switch (digit) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:       // Correct case syntax
      odd_cnt++;  // Fixed typo in variable name
      break;
    case 2:
    case 4:
    case 6:
    case 8:
    case 0:        // 10→0 (digit%10 can't be 10)
      even_cnt++;  // Fixed typo in variable name
      break;
  }

  // --- Part (d) Correction ---
  constexpr unsigned ival = 512, jval = 1024, kval = 4096;  // Must be const
  unsigned buf_size;
  unsigned swt = GetBufCnt();
  switch (swt) {
    case ival:
      buf_size = ival * sizeof(int);
      break;
    case jval:
      buf_size = jval * sizeof(int);
      break;
    case kval:
      buf_size = kval * sizeof(int);
      break;
  }

  return 0;
}
