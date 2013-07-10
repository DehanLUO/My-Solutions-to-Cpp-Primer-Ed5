/*
 * Exercise 15.8: Define static type and dynamic type.
 */

/*
 * COMPREHENSIVE TYPE SYSTEM ANALYSIS:
 *
 * STATIC TYPE (Compile-time):
 * - Determined by the declared type in the source code
 * - Known at compile time and never changes
 * - Governs static binding and member access rules
 * - Determines which operations are syntactically valid
 * - Used for overload resolution and template instantiation
 *
 * DYNAMIC TYPE (Run-time):
 * - Refers to the actual type of the object being referenced
 * - Determined at runtime and can vary during execution
 * - Governs dynamic dispatch for virtual functions
 * - Accessible through RTTI (typeid, dynamic_cast)
 * - Essential for polymorphic behavior implementation
 *
 * KEY DIFFERENCES:
 * 1. Binding Time:
 *    - Static type: Compile-time
 *    - Dynamic type: Run-time
 *
 * 2. Function Dispatch:
 *    - Static type: Determines non-virtual function calls
 *    - Dynamic type: Determines virtual function calls
 *
 * 3. Member Access:
 *    - Static type: Determines which members are accessible
 *    - Dynamic type: Determines actual implementation executed
 *
 * 4. Type Safety:
 *    - Static type: Enforced by compiler, prevents invalid operations
 *    - Dynamic type: Requires explicit checks (dynamic_cast) for safety
 *
 * PRACTICAL IMPLICATIONS:
 * - Virtual functions enable behavior based on dynamic type
 * - Non-virtual functions always use static type binding
 * - dynamic_cast allows safe downcasting based on dynamic type
 * - typeid provides runtime type identification information
 */

#include <iostream>  // std::cout, std::ostream
#include <memory>    // std::unique_ptr
#include <typeinfo>  // typeid, std::type_info

/**
 * @class Base
 * @brief Base class demonstrating polymorphic behavior
 * @note Contains virtual functions to enable runtime polymorphism
 */
class Base {
 public:
  /**
   * @brief Default constructor
   */
  Base() = default;

  /**
   * @brief Virtual function for polymorphic override
   * @note Marked virtual to enable dynamic dispatch
   */
  virtual void Display() const {
    std::cout << "Base::Display() implementation\n";
  }

  /**
   * @brief Virtual destructor for proper polymorphic cleanup
   * @note Essential when dealing with inheritance and polymorphism
   */
  virtual ~Base() = default;

  /**
   * @brief Non-virtual function demonstrating static binding
   */
  void Show() const { std::cout << "Base::Show() non-virtual function\n"; }
};

/**
 * @class Derived
 * @brief Derived class overriding base virtual functions
 * @note Provides specific implementation while maintaining base interface
 */
class Derived : public Base {
 public:
  /**
   * @brief Override of base virtual function
   * @note Uses override keyword for compile-time safety
   */
  void Display() const override {
    std::cout << "Derived::Display() override implementation\n";
  }

  /**
   * @brief Derived-specific function not in base interface
   */
  void SpecialFunction() const {
    std::cout << "Derived::SpecialFunction() unique to Derived\n";
  }
};

/**
 * @class AnotherDerived
 * @brief Another derived class for additional demonstration
 */
class AnotherDerived : public Base {
 public:
  /**
   * @brief Different override implementation
   */
  void Display() const override {
    std::cout << "AnotherDerived::Display() different override\n";
  }
};

/**
 * @brief Demonstrate type information using different mechanisms
 * @param base_ptr Pointer to Base object (could be Base or Derived)
 * @note Shows how static and dynamic types differ in polymorphic contexts
 */
void DemonstrateTypes(Base* base_ptr) {
  if (!base_ptr) return;

  std::cout << "\n=== Type Analysis ===\n";

  /*
   * STATIC TYPE ANALYSIS (Compile-time):
   * The static type is the type declared in the source code and known
   * at compile time. It determines which members are accessible and
   * governs static binding.
   */
  std::cout << "Accessible members from static type:\n";
  // Virtual function (dynamic dispatch at run-time)
  base_ptr->Display();
  // Non-virtual function (static binding at compile-time)
  base_ptr->Show();

  /*
   * DYNAMIC TYPE ANALYSIS (Run-time):
   * The dynamic type is the actual type of the object being pointed to
   * at runtime. It determines which virtual function implementation
   * is executed through dynamic dispatch.
   */
  std::cout << "\nDynamic type (run-time): ";

  // Using typeid for runtime type identification (RTTI)
  const std::type_info& type_info = typeid(*base_ptr);
  std::cout << type_info.name() << "\n";

  // Using dynamic_cast for type-safe downcasting
  Derived* derived_ptr = dynamic_cast<Derived*>(base_ptr);
  if (derived_ptr) {
    std::cout << "Object is actually of type Derived - downcast successful\n";
    derived_ptr->SpecialFunction();  // Access Derived-specific function
  } else {
    std::cout << "Object is not of type Derived - downcast failed\n";
  }

  // Demonstrating virtual function call based on dynamic type
  std::cout << "Virtual function call (dynamic dispatch): ";
  base_ptr->Display();
}

/**
 * @brief Main function illustrating static vs dynamic type concepts
 * @return Exit status code (0 for success)
 * @note Comprehensive demonstration of type system behavior in polymorphism
 */
int main() {
  std::cout << "=== Static Type vs Dynamic Type Analysis ===\n\n";

  {
    // Scenario 1: Base object through base pointer
    std::cout << "1. Base object through Base pointer:\n";
    Base base_obj;
    Base* base_ptr = &base_obj;
    DemonstrateTypes(base_ptr);
  }

  {
    // Scenario 2: Derived object through base pointer
    std::cout << "\n\n2. Derived object through Base pointer:\n";
    Derived derived_obj;
    Base* base_ptr = &derived_obj;
    DemonstrateTypes(base_ptr);
  }

  {
    // Scenario 3: AnotherDerived object through base pointer
    std::cout << "\n\n3. AnotherDerived object through Base pointer:\n";
    AnotherDerived another_derived_obj;
    Base* base_ptr = &another_derived_obj;
    DemonstrateTypes(base_ptr);
  }

  {
    // Scenario 4: Using smart pointers with C++11 compatible syntax
    std::cout << "\n\n4. Smart pointer demonstration (C++11 compatible):\n";
    std::unique_ptr<Base> smart_ptr(
        new Derived());  // C++11 compatible initialization
    DemonstrateTypes(smart_ptr.get());
  }

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-08.cc && ./main
 * === Static Type vs Dynamic Type Analysis ===
 *
 * 1. Base object through Base pointer:
 *
 * === Type Analysis ===
 * Accessible members from static type:
 * Base::Display() implementation
 * Base::Show() non-virtual function
 *
 * Dynamic type (run-time): 4Base
 * Object is not of type Derived - downcast failed
 * Virtual function call (dynamic dispatch): Base::Display() implementation
 *
 *
 * 2. Derived object through Base pointer:
 *
 * === Type Analysis ===
 * Accessible members from static type:
 * Derived::Display() override implementation
 * Base::Show() non-virtual function
 *
 * Dynamic type (run-time): 7Derived
 * Object is actually of type Derived - downcast successful
 * Derived::SpecialFunction() unique to Derived
 * Virtual function call (dynamic dispatch): Derived::Display() override implementation
 *
 *
 * 3. AnotherDerived object through Base pointer:
 *
 * === Type Analysis ===
 * Accessible members from static type:
 * AnotherDerived::Display() different override
 * Base::Show() non-virtual function
 *
 * Dynamic type (run-time): 14AnotherDerived
 * Object is not of type Derived - downcast failed
 * Virtual function call (dynamic dispatch): AnotherDerived::Display() different override
 *
 *
 * 4. Smart pointer demonstration (C++11 compatible):
 *
 * === Type Analysis ===
 * Accessible members from static type:
 * Derived::Display() override implementation
 * Base::Show() non-virtual function
 *
 * Dynamic type (run-time): 7Derived
 * Object is actually of type Derived - downcast successful
 * Derived::SpecialFunction() unique to Derived
 * Virtual function call (dynamic dispatch): Derived::Display() override implementation
 */
