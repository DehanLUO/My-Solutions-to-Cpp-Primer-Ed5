/*
 * Exercise 16.35: Which, if any, of the following calls are errors? If the call
 * is legal, what is the type of T? If the call is not legal, what is the
 * problem?
 *     template <typename T> T calc(T, int);
 *     template <typename T> T fcn(T, T);
 *     double d;    float f;    char c;
 *     (a) calc(c, ’c’); (b) calc(d, f);
 *     (c) fcn(c, ’c’);  (d) fcn(d, f);
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-16/exercise-35.cc && ./main

 */
