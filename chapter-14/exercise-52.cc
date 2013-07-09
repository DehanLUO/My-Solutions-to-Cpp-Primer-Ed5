/*
 * Exercise 14.52: Which operator+, if any, is selected for each of the addition
 * expressions? List the candidate functions, the viable functions, and the type
 * conversions on the arguments for each viable function:
 *     struct LongDouble {
 *       // member operator+ for illustration purposes; + is usually a nonmember
 *       LongDouble operator+(const SmallInt&);
 *       // other members as in § 14.9.2 (p. 587)
 *     };
 *     LongDouble operator+(LongDouble&, double);
 *     SmallInt si;
 *     LongDouble ld;
 *     ld = si + ld;
 *     ld = ld + si;
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-14/exercise-52.cc && ./main

 */
