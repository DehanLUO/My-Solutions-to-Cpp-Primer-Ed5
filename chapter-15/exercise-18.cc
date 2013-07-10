/*
 * Exercise 15.18: Given the classes from page 612 and page 613, and assuming
 * each object has the type specified in the comments, determine which of these
 * assignments are legal. Explain why those that are illegal aren’t allowed:
 *     Base *p = &d1; // d1 has type Pub_Derv
 *     p = &d2;       // d2 has type Priv_Derv
 *     p = &d3;       // d3 has type Prot_Derv
 *     p = &dd1;      // dd1 has type Derived_from_Public
 *     p = &dd2;      // dd2 has type Derived_from_Private
 *     p = &dd3;      // dd3 has type Derived_from_Protected
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
};

/**
 * @struct Derived_from_Private
 * @brief Derived from privately derived class
 * @note No access to Base members due to private inheritance
 */
struct Dervied_from_Private : public Priv_Derv {
  // error: Base::prot_mem is private in Priv_Derv
  // int use_base() { return prot_mem; }
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
};

int main() {
  Pub_Derv d1;   // members inherited from Base are public
  Priv_Derv d2;  // members inherited from Base are private
  Prot_Derv d3;  // members inherited from Base are protected

  Dervied_from_Public dd1;
  Dervied_from_Private dd2;
  Dervied_from_Portected dd3;

  Base* p = nullptr;

  // LEGAL: Public inheritance preserves is-a relationship
  p = &d1;  // d1 has type Pub_Derv

  /*
   * ILLEGAL: Private inheritance makes Base members private
   * - Priv_Derv does NOT expose Base's public interface
   * - Cannot convert Priv_Derv* to Base* outside class scope
   */
  // p = &d2;  // d2 has type Priv_Derv

  /*
   * ILLEGAL: Protected inheritance restricts Base interface
   * - Base's public members become protected in Prot_Derv
   * - Cannot access Base interface outside inheritance hierarchy
   */
  // p = &d3;  // d3 has type Prot_Derv

  /*
   * LEGAL: Public inheritance chain preserves accessibility
   * - Pub_Derv → Base: public inheritance
   * - Derived_from_Public → Pub_Derv: public inheritance
   * - Base interface remains accessible
   */
  p = &dd1;  // dd1 has type Derived_from_Public

  /*
   * ILLEGAL: Private inheritance breaks accessibility chain
   * - Priv_Derv → Base: private inheritance
   * - Base members are private in Priv_Derv
   * - Derived_from_ublic cannot access Base through Priv_Derv
   */
  // p = &dd2;  // dd2 has type Derived_from_Private

  /*
   * ILLEGAL: Protected inheritance restricts access
   * - Prot_Derv → Base: protected inheritance
   * - Base's public interface becomes protected in Prot_Derv
   * - Cannot convert to Base* outside protected hierarchy
   */
  // p = &dd3;  // dd3 has type Derived_from_Protected

  return 0;
}
