
// Exercise 1.8: Indicate which, if any, of the following output statements are
// legal:
//     std::cout << "/*";
//     std::cout << "*/";
//     std::cout << /* "*/" */;
//     std::cout << /*  "*/" /*  "/*" */;
// After you’ve predicted what will happen, test your answers by compiling a
// program with each of these statements.Correct any errors you encounter.

// Analysis of the Output Satements
// 1. std::cout << "/*";
// 2. std::cout << "*/";
// - Legal: The correctly outputs the string "/*" and "*/".
// - The string is properly enclosed in the double quotes.
// 3. std::cout << /* "*/" */;
// - Illegal: The first `/*` starts a comment, causing the first `"" to be
// ignored.
// - The compiler sees `" */;`, whis is an unterminated string (`"` is missing
// its closing quote).
// 4. std::cout << /*  "*/" /*  "/*" */;
// - Legal: The first `/*` comments out `"`, The third `/*` comments out `"`,
// leving `"  /*  "` as the output.

#include <iostream>  // std::cout

int main() {
  std::cout << "/*";
  std::cout << "*/";
  std::cout << /* "*/ " */";  // Fix: Add a closing quote.
  std::cout << /*  "*/ " /*  " /*" */;
}