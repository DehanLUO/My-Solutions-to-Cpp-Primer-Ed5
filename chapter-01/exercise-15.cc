/*
 * Exercise 1.15: Write programs that contain the common errors discussed in the
 * box on page 16. Familiarize yourself with the messages the compiler
 * generates.
 */

#include <iostream>  // std::cout
/*
 * // error: missing ) in parameter list for main
 * int main({
 *   // error: used colon, not a semicolon, after endl
 *   std::cout << "Read each file." << std::endl:
 *   // error: missing quotes around string literal
 *   std::cout << Update master. << std::endl;
 *   // error: second output operator is missing
 *   std::cout << "Write new master." std::endl;
 *   // error: missing ; on return statement
 *   return 0
 * }
 */

/*
 * $ g++ -o main exercise-15.cc
 * exercise-15.cc:10:1: error: main cannot be declared as global variable
 *    10 | int main({
 *       | ^
 * exercise-15.cc:12:47: error: expected '}'
 *    12 |   std::cout << "Read each file." << std::endl:
 *       |                                              ^
 * exercise-15.cc:10:10: note: to match this '{'
 *    10 | int main({
 *       |          ^
 * exercise-15.cc:19:2: error: expected ';' after top level declarator
 *    19 | }
 *       |  ^
 *       |  ;
 * 3 errors generated.
 */

/*
 * int main() {
 *   // error: used colon, not a semicolon, after endl
 *   std::cout << "Read each file." << std::endl:
 *   // error: missing quotes around string literal
 *   std::cout << Update master. << std::endl;
 *   // error: second output operator is missing
 *   std::cout << "Write new master." std::endl;
 *   // error: missing ; on return statement
 *   return 0
 * }
 */

/*
 * $ g++ -o main exercise-15.cc
 * exercise-15.cc:43:46: error: expected ';' after expression
 *    43 |   std::cout << "Read each file." << std::endl:
 *       |                                              ^
 *       |                                              ;
 * exercise-15.cc:45:22: error: expected ';' after expression
 *    45 |   std::cout << Update master. << std::endl;
 *       |                      ^
 *       |                      ;
 * exercise-15.cc:45:16: error: use of undeclared identifier 'Update'
 *    45 |   std::cout << Update master. << std::endl;
 *       |                ^
 * exercise-15.cc:45:23: error: use of undeclared identifier 'master'
 *    45 |   std::cout << Update master. << std::endl;
 *       |                       ^
 * exercise-15.cc:45:31: error: expected unqualified-id
 *    45 |   std::cout << Update master. << std::endl;
 *       |                               ^
 * exercise-15.cc:47:35: error: expected ';' after expression
 *    47 |   std::cout << "Write new master." std::endl;
 *       |                                   ^
 *       |                                   ;
 * exercise-15.cc:47:36: error: reference to overloaded function could not be resolved; did you mean to call it?
 *    47 |   std::cout << "Write new master." std::endl;
 *       |                                    ^~~~~~~~~
 * /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__ostream/basic_ostream.h:723:62: note: possible target for call
 *   723 | _LIBCPP_HIDE_FROM_ABI inline basic_ostream<_CharT, _Traits>& endl(basic_ostream<_CharT, _Traits>& __os) {
 *       |                                                              ^
 * exercise-15.cc:49:11: error: expected ';' after return statement
 *    49 |   return 0
 *       |           ^
 *       |           ;
 * 8 errors generated.
 */

/*
 * int main() {
 *   std::cout << "Read each file." << std::endl;
 *   // error: missing quotes around string literal
 *   std::cout << Update master. << std::endl;
 *   // error: second output operator is missing
 *   std::cout << "Write new master." std::endl;
 *   // error: missing ; on return statement
 *   return 0
 * }
 */

/*
 * $ g++ -o main exercise-15.cc
 * exercise-15.cc:93:22: error: expected ';' after expression
 *    93 |   std::cout << Update master. << std::endl;
 *       |                      ^
 *       |                      ;
 * exercise-15.cc:93:16: error: use of undeclared identifier 'Update'
 *    93 |   std::cout << Update master. << std::endl;
 *       |                ^
 * exercise-15.cc:93:23: error: use of undeclared identifier 'master'
 *    93 |   std::cout << Update master. << std::endl;
 *       |                       ^
 * exercise-15.cc:93:31: error: expected unqualified-id
 *    93 |   std::cout << Update master. << std::endl;
 *       |                               ^
 * exercise-15.cc:95:35: error: expected ';' after expression
 *    95 |   std::cout << "Write new master." std::endl;
 *       |                                   ^
 *       |                                   ;
 * exercise-15.cc:95:36: error: reference to overloaded function could not be resolved; did you mean to call it?
 *    95 |   std::cout << "Write new master." std::endl;
 *       |                                    ^~~~~~~~~
 * /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__ostream/basic_ostream.h:723:62: note: possible target for call
 *   723 | _LIBCPP_HIDE_FROM_ABI inline basic_ostream<_CharT, _Traits>& endl(basic_ostream<_CharT, _Traits>& __os) {
 *       |                                                              ^
 * exercise-15.cc:97:11: error: expected ';' after return statement
 *    97 |   return 0
 *       |           ^
 *       |           ;
 * 7 errors generated.
 */

/*
 * int main() {
 *   std::cout << "Read each file." << std::endl;
 *   std::cout << Update master. << std::endl;
 *   // error: second output operator is missing
 *   std::cout << "Write new master." std::endl;
 *   // error: missing ; on return statement
 *   return 0
 * }
 */

/*
 * $ g++ -o main exercise-15.cc
 * exercise-15.cc:138:35: error: expected ';' after expression
 *   138 |   std::cout << "Write new master." std::endl;
 *       |                                   ^
 *       |                                   ;
 * exercise-15.cc:138:36: error: reference to overloaded function could not be resolved; did you mean to call it?
 *   138 |   std::cout << "Write new master." std::endl;
 *       |                                    ^~~~~~~~~
 * /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/__ostream/basic_ostream.h:723:62: note: possible target for call
 *   723 | _LIBCPP_HIDE_FROM_ABI inline basic_ostream<_CharT, _Traits>& endl(basic_ostream<_CharT, _Traits>& __os) {
 *       |                                                              ^
 * exercise-15.cc:140:11: error: expected ';' after return statement
 *   140 |   return 0
 *       |           ^
 *       |           ;
 * 3 errors generated.
 */

/*
 * int main() {
 *   std::cout << "Read each file." << std::endl;
 *   std::cout << Update master. << std::endl;
 *   std::cout << "Write new master." std::endl;
 *   // error: missing ; on return statement
 *   return 0
 * }
 */

/*
 * $ g++ -o main exercise-15.cc
 * exercise-15.cc:169:11: error: expected ';' after return statement
 *   169 |   return 0
 *       |           ^
 *       |           ;
 * 1 error generated.
 */

int main() {
  int v1 = 0, v2 = 0;
  std::cin >> v >> v2;  // error: uses "v" not "v1"
  // error: cout not defined; should be std::cout
  cout << v1 + v2 << std::endl;
  return 0;
}

/*
 * $ g++ -o main exercise-15.cc
 * exercise-15.cc:184:15: error: use of undeclared identifier 'v'
 *   184 |   std::cin >> v >> v2; // error: uses "v" not "v1"
 *       |               ^
 * exercise-15.cc:186:3: error: use of undeclared identifier 'cout'; did you mean 'std::cout'?
 *   186 |   cout << v1 + v2 << std::endl; 
 *       |   ^~~~
 *       | std::cout
 * /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/iostream:54:42: note: 'std::cout' declared here
 *    54 | extern _LIBCPP_EXPORTED_FROM_ABI ostream cout;
 *       |                                          ^
 * 2 errors generated.
 */
