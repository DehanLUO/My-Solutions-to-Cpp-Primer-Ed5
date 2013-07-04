/*
 * Exercise 7.56: What is a static class member? What are the advantages of
 * static members? How do they differ from ordinary members?
 */

/**
 * @brief Definition of static class members
 */
/*
 * A static class member is a member that:
 * 1. Is associated with the class itself, not individual objects
 * 2. Has single storage duration for all class instances
 * 3. Exists independently of any class instances
 *
 */
class MyClass {
  static int class_wide_var;  // Declaration
};
int MyClass::class_wide_var = 0;  // Definition

/**
 * @brief Key advantages of static members
 */
/*
 * 1. Shared State Management:
 *    - Single instance shared across all objects
 *    - Avoids redundant storage
 *
 * 2. Class-Level Operations:
 *    - Can be used without object instantiation
 *    - Enables factory patterns
 *
 * 3. Lifetime Control:
 *    - Program duration lifetime
 *    - Initialization order control
 *
 * 4. Access Control:
 *    - Can be private/protected like instance members
 *    - Public static members act as namespaced globals
 */

/**
 * @brief Comparison with ordinary members
 */
/*
 * | Feature          | Static Members       | Ordinary Members     |
 * |------------------|----------------------|----------------------|
 * | Storage          | Single copy          | Per-object copy      |
 * | Access           | Class::member        | object.member        |
 * | Lifetime         | Program duration     | Object lifetime      |
 * | this pointer     | Not available        | Available            |
 * | const-ness       | Separate for objects | Per-object           |
 */
