/*
 * Exercise 1.2: Change the program to return -1. A return value of -1 is often
 * treated as an indicator that the program failed. Recompile and rerun your
 * program to see how your system treats a failure indicator from main.
 */

int main() { return -1; }

/*
 * $ g++ -o main exercise01-02.cc
 * $ ./main
 * $ echo $?
 * 255
 */

/*
 * Explanation of Return Value -1 Showing as 255
 * The reason I am  seeing 255 instead of -1 when checking the return value
 * throuth `echo $?` is due to how unix-like systems handle exit status from
 * programs.
 *
 * 1. Exit Status Convention: In unix-like systems, exit statuses are unsigned
 * 8-bit integers (values from 0 to 255).
 *
 * 2. Negative Values: When I return -1 from main(), it is actually represented
 * in binary as all bits set (11111111 in 8-bit two's complement).
 *
 * 3. Truncation to 8 Bits: The system only keeps the lowest 8 bits of the
 * return value. For -1 (which if 0xFFFFFFFF in 32-bit or 0xFFFFFFFFFFFFFFFF in
 * 64-bit), this becomes 255(0xFF).
 *
 * 4. Success/Failure Convention: While 0 typically means success, any non-zero
 * value (1-255) indicates some form of failure. The specific value can indicate
 * different error conditions.
 */