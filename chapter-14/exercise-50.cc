/*
 * Exercise 14.50: Show the possible class-type conversion sequences for the
 * initializations of ex1 and ex2. Explain whether the initializations are legal
 * or not.
 *     struct LongDouble {
 *       LongDouble(double = 0.0);
 *       operator double();
 *       operator float();
 *     };
 *     LongDouble ldObj;
 *     int ex1 = ldObj;
 *     float ex2 = ldObj;
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-14/exercise-50.cc && ./main

 */
