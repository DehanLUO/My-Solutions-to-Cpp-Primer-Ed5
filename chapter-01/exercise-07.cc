/*
 * Exercise 1.7: Compile a program that has incorrectly nested comments.
 */

/*
 * comment pairs /*  */cannot nest.
 * "cannot nest" is considered source code,
 * as is the rest of the program
 */
int main() { return 0; }

/*
 * $ g++ -o main exercise-07.cc && ./main
 * exercise-07.cc:6:18: warning: '/*' within block comment [-Wcomment]
 *     6 |  * comment pairs /*  */cannot nest.
 *       |                  ^
 * exercise-07.cc:6:24: error: unknown type name 'cannot'
 *     6 |  * comment pairs /*  */cannot nest.
 *       |                        ^
 * exercise-07.cc:6:35: error: expected ';' after top level declarator
 *     6 |  * comment pairs /*  */cannot nest.
 *       |                                   ^
 *       |                                   ;
 * 1 warning and 2 errors generated.
 */