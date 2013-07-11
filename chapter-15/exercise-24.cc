/*
 * Exercise 15.24: What kinds of classes need a virtual destructor? What
 * operations must a virtual destructor perform?
 */

#include <iostream>  // std::cout

/**
 * @class BaseWithoutVirtualDestructor
 * @brief Base class without virtual destructor (PROBLEMATIC)
 * @note Demonstrates the issues that arise when virtual destructor is missing
 */
class BaseWithoutVirtualDestructor {
 public:
  /**
   * @brief Constructor
   */
  BaseWithoutVirtualDestructor() {
    std::cout << "BaseWithoutVirtualDestructor constructor\n";
  }

  /**
   * @brief NON-virtual destructor (PROBLEM)
   * @note This will cause issues when deleting through base pointers
   */
  ~BaseWithoutVirtualDestructor() {
    std::cout << "BaseWithoutVirtualDestructor destructor\n";
  }

  /**
   * @brief Virtual function for polymorphism
   */
  virtual void DoSomething() {
    std::cout << "BaseWithoutVirtualDestructor::DoSomething()\n";
  }
};

/**
 * @class DerivedWithoutVirtualDestructor
 * @brief Derived class from base without virtual destructor
 * @note Shows the resource leak problem
 */
class DerivedWithoutVirtualDestructor : public BaseWithoutVirtualDestructor {
 public:
  /**
   * @brief Constructor with resource allocation
   */
  DerivedWithoutVirtualDestructor() : resource_(new int(42)) {
    std::cout << "DerivedWithoutVirtualDestructor constructor\n";
  }

  /**
   * @brief Destructor that should cleanup resources
   * @note This destructor may not be called if deleted through base pointer
   */
  ~DerivedWithoutVirtualDestructor() {
    delete resource_;
    std::cout << "DerivedWithoutVirtualDestructor destructor\n";
  }

  void DoSomething() override {
    std::cout << "DerivedWithoutVirtualDestructor::DoSomething()\n";
  }

 private:
  int* resource_;  // Dynamically allocated resource
};

/**
 * @class BaseWithVirtualDestructor
 * @brief Base class with proper virtual destructor (CORRECT)
 * @note Demonstrates correct virtual destructor implementation
 */
class BaseWithVirtualDestructor {
 public:
  /**
   * @brief Constructor
   */
  BaseWithVirtualDestructor() {
    std::cout << "BaseWithVirtualDestructor constructor\n";
  }

  /**
   * @brief Virtual destructor (ESSENTIAL)
   * @note Ensures proper cleanup of derived classes through base pointers
   */
  virtual ~BaseWithVirtualDestructor() {
    std::cout << "BaseWithVirtualDestructor destructor\n";
  }

  virtual void DoSomething() {
    std::cout << "BaseWithVirtualDestructor::DoSomething()\n";
  }
};

/**
 * @class DerivedWithVirtualDestructor
 * @brief Derived class from base with virtual destructor
 * @note Shows proper resource cleanup
 */
class DerivedWithVirtualDestructor : public BaseWithVirtualDestructor {
 public:
  /**
   * @brief Constructor with resource allocation
   */
  DerivedWithVirtualDestructor() : resource_(new int(42)) {
    std::cout << "DerivedWithVirtualDestructor constructor\n";
  }

  /**
   * @brief Destructor that cleans up resources
   * @note This will be called properly due to virtual destructor in base
   */
  ~DerivedWithVirtualDestructor() override {
    delete resource_;
    std::cout << "DerivedWithVirtualDestructor destructor\n";
  }

  void DoSomething() override {
    std::cout << "DerivedWithVirtualDestructor::DoSomething()\n";
  }

 private:
  int* resource_;  // Dynamically allocated resource
};

/**
 * @brief Main function demonstrating virtual destructor requirements
 * @return Exit status code (0 for success)
 * @note Shows both problematic and correct scenarios
 */
int main() {
  /*
   * CLASSES THAT NEED VIRTUAL DESTRUCTORS:
   * a) POLYMORPHIC BASE CLASSES:
   *    - Any class intended to be used as a base class
   *    - That will be used polymorphically (through base pointers/references)
   *    - That has at least one virtual function
   * b) CLASSES WITH VIRTUAL FUNCTIONS:
   *    - If a class has any virtual functions
   *    - It should almost always have a virtual destructor
   *    - This ensures proper cleanup of derived objects
   * c) CLASSES IN INHERITANCE HIERARCHIES:
   *    - Base classes in inheritance hierarchies
   *    - Even if not currently used polymorphically
   *    - Future extensions might require polymorphism
   */

  /*
   * PART 2: DEMONSTRATION OF PROBLEMS WITHOUT VIRTUAL DESTRUCTOR
   */

  // Scenario: Deleting derived object through base pointer
  BaseWithoutVirtualDestructor* bad_ptr = new DerivedWithoutVirtualDestructor();

  // Calling delete on base pointer
  delete bad_ptr;  // UNDEFINED BEHAVIOR: Derived destructor not called!
  std::cout << '\n';

  /*
   * PART 3: CORRECT USAGE WITH VIRTUAL DESTRUCTOR
   */

  // Scenario: Deleting derived object through base pointer

  BaseWithVirtualDestructor* good_ptr = new DerivedWithVirtualDestructor();

  // Calling delete on base pointer
  delete good_ptr;  // CORRECT: Both base and derived destructors called

  /*
   * PART 4: VIRTUAL DESTRUCTOR OPERATIONS AND RESPONSIBILITIES
   * a) DESTRUCTION ORDER:
   *    - Derived destructor called first (most derived class)
   *    - Then base destructors in reverse inheritance order
   *    - Automatic chaining through virtual dispatch
   * b) RESOURCE CLEANUP:
   *    - Release derived-class-specific resources
   *    - Call base class destructors automatically
   *    - Ensure no memory leaks or resource leaks
   * c) EXCEPTION SAFETY:
   *    - Destructors should not throw exceptions
   *    - If exceptions might occur, handle within destructor
   *    - Use noexcept specification where appropriate
   */

  /*
   * PART 5: WHEN VIRTUAL DESTRUCTOR IS NOT NEEDED
   * a) FINAL CLASSES:
   *    - Classes not intended to be derived from
   *    - Mark with 'final' keyword (C++11+)
   * b) NON-POLYMORPHIC CLASSES:
   *    - Classes without any virtual functions
   *    - Not used as base classes for polymorphism
   * c) VALUE SEMANTICS CLASSES:
   *    - Classes used primarily by value
   *    - Not managed through pointers/references
   */

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-24.cc && ./main
 * BaseWithoutVirtualDestructor constructor
 * DerivedWithoutVirtualDestructor constructor
 * BaseWithoutVirtualDestructor destructor
 *
 * BaseWithVirtualDestructor constructor
 * DerivedWithVirtualDestructor constructor
 * DerivedWithVirtualDestructor destructor
 * BaseWithVirtualDestructor destructor
 */
