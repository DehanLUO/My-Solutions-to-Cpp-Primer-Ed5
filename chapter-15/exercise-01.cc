/*
 * Exercise 15.1: What is a virtual member?
 */

/*
 * 1. Dynamic Binding Mechanism:
 *    Virtual functions use vtables (virtual tables) that contain function
 *    pointers, allowing runtime determination of the appropriate function
 *    to call based on the actual object type rather than the pointer type.
 *
 * 2. Memory Overhead:
 *    Each object with virtual functions contains a vptr (virtual pointer)
 *    that points to its class's vtable, adding typically one pointer size
 *    per object overhead.
 *
 * 3. Override Requirements:
 *    Derived class functions must have identical signatures (return type,
 *    parameters, and const-qualification) to properly override base virtual
 *    functions. The 'override' keyword ensures this contract is maintained.
 *
 * 4. Virtual Destructor Necessity:
 *    When deleting objects through base pointers, virtual destructors ensure
 *    the complete destruction chain (derived then base) is properly executed.
 *
 * 5. Pure Virtual Functions:
 *    Virtual functions can be declared pure (= 0) making the class abstract
 *    and requiring derived classes to provide implementations.
 */

#include <iostream>  // std::cout, std::ostream

/**
 * @class Base
 * @brief Demonstrates virtual member function declaration and behavior
 * @note Virtual functions enable runtime polymorphism by allowing derived
 *       classes to override base class implementations
 */
class Base {
 public:
  /**
   * @brief Virtual destructor declaration
   * @note Essential for proper cleanup of derived class objects through base
   *       pointers
   */
  virtual ~Base() { std::cout << "Base destructor called\n"; }

  /**
   * @brief Virtual member function declaration
   * @note The 'virtual' keyword indicates that this function can be overridden
   *       by derived classes and will use dynamic dispatch
   */
  virtual void Display() const { std::cout << "Base::Display() called\n"; }

  /**
   * @brief Non-virtual member function
   * @note This function uses static binding and cannot be overridden
   *       polymorphically
   */
  void Show() const { std::cout << "Base::Show() called\n"; }
};

class Derived : public Base {
 public:
  /**
   * @brief Derived class destructor
   * @note Virtual destructor chain ensures proper cleanup of derived-specific
   *       resources
   */
  ~Derived() override { std::cout << "Dervied destructor called\n"; }

  /**
   * @brief Override of base class virtual function
   * @note The 'override' keyword (C++11) ensures this function actually
   *       overrides a virtual function from the base class, providing
   *       compile-time safety
   */
  void Display() const override { std::cout << "Dervied::Display() called\n"; }
};

/**
 * @brief Demonstrates polymorphic behavior through base class pointers
 * @param ptr Pointer to Base class object
 * @note Virtual functions enable runtime determination of the actual object
 * type
 */
void DemonstratePolymorphism(const Base* ptr) {
  if (nullptr != ptr) {
    ptr->Display();  // Dynamic dispatch: calls appropriate override
    ptr->Show();     // Static binding: always calls Base::Show()
  }
}

int main() {
  {
    std::cout << "=== Creating Base object ===\n";
    Base base_obj;
    DemonstratePolymorphism(&base_obj);
  }

  {
    std::cout << "\n=== Creating Derived object ===\n";
    Derived derived_obj;
    DemonstratePolymorphism(&derived_obj);
  }

  std::cout << "\n=== Polymorphism through base pointer ===\n";
  Base* poly_ptr = new Derived();
  poly_ptr->Display();  // Calls Derived::Display() - dynamic dispatch
  poly_ptr->Show();     // Calls Base::Show() - static binding
  delete poly_ptr;      // Proper cleanup through virtual destructor

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-01.cc && ./main
 * === Creating Base object ===
 * Base::Display() called
 * Base::Show() called
 * Base destructor called
 *
 * === Creating Derived object ===
 * Dervied::Display() called
 * Base::Show() called
 * Dervied destructor called
 * Base destructor called
 *
 * === Polymorphism through base pointer ===
 * Dervied::Display() called
 * Base::Show() called
 * Dervied destructor called
 * Base destructor called
 */
