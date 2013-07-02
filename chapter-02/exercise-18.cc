/*
 * Exercise 2.18: Write code to change the value of a pointer. Write code to
 * change the value to which the pointer points.
 */

#include <iostream>  // std::cout

/**
 * @brief Dumps detailed information about two variables and a pointer.
 *
 * This function prints the following information to standard output:
 * - Values of `variable_1` and `variable_2`.
 * - The address stored in `pointer` (the address it points to) and the
 *   dereferenced value.
 * - Memory addresses of `variable_1`, `variable_2`, and the pointer itself.
 *
 * @param variable_1
 *   Reference to the first integer variable (constant, read-only).
 * @param variable_2
 *   Reference to the second integer variable (constant, read-only).
 * @param pointer
 *   Constant reference to a pointer to const int. This means:
 *   - The pointer itself cannot be modified (repointed) within this function.
 *   - The data pointed to by `pointer` is also read-only.
 *
 * @note
 *   The pointer must point to a valid memory address (non-null) when
 * dereferenced (*pointer). Undefined behaviour will occur if `pointer` is null
 * or dangling.
 */
void Dump(const int& variable_1, const int& variable_2,
          const int* const& pointer) {
  std::cout << "Value of variable_1: " << variable_1 << '\n'          //
            << "Value of variable_2: " << variable_2 << '\n'          //
            << "Value of pointer (the address): " << pointer << '\n'  //
            << "Value of pointer points: " << *pointer << '\n'        //
            << "Address of variable_1: " << &variable_1 << '\n'       //
            << "Address of variable_2: " << &variable_2 << '\n'       //
            << "Address of pointer: " << &pointer << '\n';            //
}

int main() {
  int variable_1 = 10;
  int variable_2 = 20;
  int* pointer = &variable_1;
  Dump(variable_1, variable_2, pointer);

  pointer = &variable_2;  // Change the value of a pointer.
  std::cout << "\nChange the value of a pointer.\n";
  Dump(variable_1, variable_2, pointer);

  *pointer += variable_1;  // Change the value to which the pointer points
  std::cout << "\nChange the value to which the pointer points.\n";
  Dump(variable_1, variable_2, pointer);

  return 0;
}
/*
 * $ g++ -o main exercise-18.cc && ./main
 * Value of variable_1: 10
 * Value of variable_2: 20
 * Value of pointer (the address): 0x7ff7bed14f88
 * Value of pointer points: 10
 * Address of variable_1: 0x7ff7bed14f88
 * Address of variable_2: 0x7ff7bed14f84
 * Address of pointer: 0x7ff7bed14f78
 *
 * Change the value of a pointer.
 * Value of variable_1: 10
 * Value of variable_2: 20
 * Value of pointer (the address): 0x7ff7bed14f84
 * Value of pointer points: 20
 * Address of variable_1: 0x7ff7bed14f88
 * Address of variable_2: 0x7ff7bed14f84
 * Address of pointer: 0x7ff7bed14f78
 *
 * Change the value to which the pointer points.
 * Value of variable_1: 10
 * Value of variable_2: 30
 * Value of pointer (the address): 0x7ff7bed14f84
 * Value of pointer points: 30
 * Address of variable_1: 0x7ff7bed14f88
 * Address of variable_2: 0x7ff7bed14f84
 * Address of pointer: 0x7ff7bed14f78
 */
