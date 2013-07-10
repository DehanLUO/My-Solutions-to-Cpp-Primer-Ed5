/*
 * Exercise 15.2: How does the protected access specifier differ from private?
 */

/*
 * COMPREHENSIVE ACCESS SPECIFIER ANALYSIS:
 *
 * 1. PRIVATE ACCESS:
 *    - Most restrictive access level
 *    - Accessible only within the class that declares them
 *    - Not accessible by derived classes, friends, or external code
 *    - Used for implementation details that should never be exposed
 *
 * 2. PROTECTED ACCESS:
 *    - Intermediate access level between private and public
 *    - Accessible within the declaring class and all derived classes
 *    - Not accessible by external code or unrelated classes
 *    - Used for members that should be available to derived classes
 *      but not to general users of the class
 *
 * 3. INHERITANCE INTERACTION:
 *    - Public inheritance: public stays public, protected stays protected
 *    - Protected inheritance: public becomes protected, protected stays
 *      protected
 *    - Private inheritance: both public and protected become private
 */

#include <iostream>  // std::cout

/**
 * @class Base
 * @brief Demonstrates private, protected, and public access specifiers
 * @note Private members are accessible only within the class itself,
 *       while protected members are accessible within the class and derived
 * classes
 */
class Base {
  /**
   * @brief Public constructor for object creation
   * @param priv_val Initial value for private member
   * @param prot_val Initial value for protected member
   * @param pub_val Initial value for public member
   */
 public:
  Base(int priv_val, int prot_val, int pub_val)
      : private_member_(priv_val),
        protected_member_(prot_val),
        public_member_(pub_val) {}

  /**
   * @brief Public member function accessing all access levels
   * @note Demonstrates that all access levels are accessible within the class
   */
  void DisplayAccess() const {
    std::cout << "Base class internal access:\n";
    std::cout << "Private: " << private_member_ << '\n';
    std::cout << "Protected: " << protected_member_ << '\n';
    std::cout << "Public: " << public_member_ << '\n';
  }

  /**
   * @brief Public accessor for private member
   * @return Value of private member
   * @note Provides controlled access to private data
   */
  int GetPrivateMember() const { return private_member_; }

 public:
  int public_member_;

 protected:
  int protected_member_;

 private:
  int private_member_;
};

/**
 * @class Derived
 * @brief Demonstrates access specifier behavior in inheritance
 * @note Shows how protected and private members behave differently in derived
 * classes
 */
class Derived : public Base {
 public:
  /**
   * @brief Derived class constructor
   * @param priv_val Value for base private member (accessed via base
   * constructor)
   * @param prot_val Value for base protected member
   * @param pub_val Value for base public member
   */
  Derived(int priv_val, int prot_val, int pub_val)
      : Base(priv_val, prot_val, pub_val) {}

  /**
   * @brief Demonstrates derived class access capabilities
   * @note Derived classes can access protected and public members directly,
   *       but cannot access private members of the base class
   */
  void DemonstrateDerviedAccess() const {
    std::cout << "\nDervied class access:\n";

    // Access to protected member: ALLOWED
    std::cout << "Protected member: " << protected_member_ << '\n';

    // Access to public member: ALLOWED
    std::cout << "Public member: " << public_member_ << '\n';

    /*
     * DIRECT ACCESS TO PRIVATE MEMBER: NOT ALLOWED
     * Uncommenting the following line would cause compilation error:
     * std::cout << "Private member: " << private_member << '\n';
     */

    // Private member must be accessed through public interface
    std::cout << "Private member (via GetPrivateMember()): "
              << GetPrivateMember() << '\n';
  }

  /**
   * @brief Modifies protected member directly
   * @note Demonstrates that derived classes can modify protected members
   */
  void ModifyProtected(int new_val) {
    protected_member_ = new_val;
    std::cout << "Modified protected member to: " << protected_member_ << '\n';
  }
};

void DemonstrateExternalAccess(const Base& base_obj) {
  std::cout << "\nExternal access:\n";

  // Public member access: ALLOWED
  std::cout << "Public member: " << base_obj.public_member_ << '\n';

  /*
   * PROTECTED MEMBER ACCESS: NOT ALLOWED
   * Uncommenting would cause compilation error:
   * std::cout << "Protected member: " << base_obj.protected_member << '\n';
   */

  /*
   * PRIVATE MEMBER ACCESS: NOT ALLOWED
   * Uncommenting would cause compilation error:
   * std::cout << "Private member: " << base_obj.private_member << '\n';
   */

  // Private member access through public interface: ALLOWED
  std::cout << "Private member (via GetPrivateMember()): "
            << base_obj.GetPrivateMember() << '\n';
}

int main() {
  {
    Base base(100, 200, 300);
    base.DisplayAccess();
  }

  {
    Derived derived(400, 500, 600);
    derived.DemonstrateDerviedAccess();

    DemonstrateExternalAccess(derived);

    derived.ModifyProtected(999);
    derived.DemonstrateDerviedAccess();
  }

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-02.cc && ./main
 * Base class internal access:
 * Private: 100
 * Protected: 200
 * Public: 300
 *
 * Dervied class access:
 * Protected member: 500
 * Public member: 600
 * Private member (via GetPrivateMember()): 400
 *
 * External access:
 * Public member: 600
 * Private member (via GetPrivateMember()): 400
 * Modified protected member to: 999
 *
 * Dervied class access:
 * Protected member: 999
 * Public member: 600
 * Private member (via GetPrivateMember()): 400
 */
