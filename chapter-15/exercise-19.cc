/*
 * Exercise 15.19: Assume that each of the classes from page 612 and page 613
 * has a member function of the form:
 *     void memfcn(Base &b) { b = *this; }
 * For each class, determine whether this function would be legal.
 */

/*
 * GENERAL RULES SUMMARY:
 *
 * The assignment 'b = *this;' is legal if:
 * - The conversion from Derived* to Base& is accessible, AND
 * - The assignment operator (Base::operator=) is accessible
 *
 * Accessibility depends on:
 * 1. Inheritance access specifier (public/protected/private)
 * 2. Where the assignment occurs (within class scope vs. outside)
 * 3. The inheritance chain accessibility
 */

/*
 * LEGAL:
 *   Pub_Derv::memfcn()               - Public inheritance
 *   Priv_Derv::memfcn()              - Within class scope
 *   Prot_Derv::memfcn()              - Within class scope
 *   Derived_from_Public::memfcn()    - Public inheritance chain
 *   Derived_from_Protected::memfcn() - Within protected hierarchy
 *
 * ILLEGAL:
 *   Derived_from_Private::memfcn()   - Base interface inaccessible
 */

#include <iostream>  // std::cout

/**
 * @class Base
 * @brief Base class with public, protected, and private members
 * @note Demonstrates member access control in inheritance
 */
class Base {
 public:
  /**
   * @brief Default constructor
   */
  Base() : prot_mem(42), priv_mem('a') {}

  /**
   * @brief Virtual destructor for proper cleanup
   */
  virtual ~Base() = default;

  /**
   * @brief Public member function
   */
  void pub_mem() { std::cout << "Base::pub_mem() called\n"; }

  /**
   * @brief Member function that assigns parameter to current object
   * @param b Reference to Base object
   * @note This is the function we are analyzing for legality in derived classes
   */
  void memfcn(Base& b) { b = *this; }

 protected:
  int prot_mem;  // protected member
 private:
  char priv_mem;  // private member
};

/**
 * @struct Pub_Derv
 * @brief Derived class with public inheritance
 * @note Base class members retain their original access levels
 */
struct Pub_Derv : public Base {
  /**
   * @brief Access protected member (allowed)
   * @return Protected member value
   */
  int f() {
    return prot_mem;
  }  // ok:: derived classes can access protected members

  // error: private members are inaccessible to derived classes
  // char g() { return priv_mem; }

  /**
   * @brief Member function assignment analysis
   * @param b Reference to Base object
   * @note LEGAL: Public inheritance preserves Base interface accessibility
   */
  void memfcn(Base& b) { b = *this; }  // LEGAL: Public inheritance
};

/**
 * @struct Priv_Derv
 * @brief Derived class with private inheritance
 * @note All Base class members become private in derived class
 */
struct Priv_Derv : private Base {
  /**
   * @brief Access protected member (allowed within class)
   * @return Protected member value
   */
  int f() const { return prot_mem; }  // ok: accessible within derived class

  /**
   * @brief Member function assignment analysis
   * @param b Reference to Base object
   * @note LEGAL: Private inheritance allows access within derived class
   */
  void memfcn(Base& b) { b = *this; }  // LEGAL: Within class scope
};

/**
 * @struct Prot_Derv
 * @brief Derived class with protected inheritance
 * @note Base class public members become protected in derived class
 */
struct Prot_Derv : protected Base {
  /**
   * @brief Access protected member (allowed)
   * @return Protected member value
   */
  int f() const { return prot_mem; }  // ok: accessible within derived class

  /**
   * @brief Member function assignment analysis
   * @param b Reference to Base object
   * @note LEGAL: Protected inheritance allows access within derived class
   */
  void memfcn(Base& b) { b = *this; }  // LEGAL: Within class scope
};

/**
 * @struct Derived_from_Public
 * @brief Derived from publicly derived class
 * @note Access levels preserved through public inheritance chain
 */
struct Dervied_from_Public : public Pub_Derv {
  /**
   * @brief Access protected member from base of base
   * @return Protected member value
   */
  int use_base() {
    return prot_mem;
  }  // ok: Base::prot_mem remains protected in Pub_Derv

  /**
   * @brief Member function assignment analysis
   * @param b Reference to Base object
   * @note LEGAL: Public inheritance chain preserves accessibility
   */
  void memfcn(Base& b) { b = *this; }  // LEGAL: Public inheritance chain
};

/**
 * @struct Derived_from_Private
 * @brief Derived from privately derived class
 * @note No access to Base members due to private inheritance
 */
struct Dervied_from_Private : public Priv_Derv {
  // error: Base::prot_mem is private in Priv_Derv
  // int use_base() { return prot_mem; }

  // ILLEGAL: Private inheritance breaks Base interface accessibility
  // void memfcn(Base& b) { b = *this; }  // ILLEGAL: Base inaccessible
};

/**
 * @struct Derived_from_Public
 * @brief Derived from publicly derived class
 * @note Access levels preserved through public inheritance chain
 */
struct Dervied_from_Portected : public Prot_Derv {
  /**
   * @brief Access protected member from base of base
   * @return Protected member value
   */
  int use_base() {
    return prot_mem;
  }  // ok: Base::prot_mem remains protected in Prot_Derv

  /**
   * @brief Member function assignment analysis
   * @param b Reference to Base object
   * @note LEGAL: Protected inheritance allows access within hierarchy
   */
  void memfcn(Base& b) { b = *this; }  // LEGAL: Within protected hierarchy
};

int main() { return 0; }