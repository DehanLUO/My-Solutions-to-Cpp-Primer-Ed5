/*
 * Exercise 15.4: Which of the following declarations, if any, are incorrect?
 * Explain why.
 *     class Base { ... };
 *     (a) class Derived : public Derived { ... };
 *     (b) class Derived : private Base { ... };
 *     (c) class Derived : public Base;
 */

/*
 * (a): class Derived : public Derived { ... };
 * INCORRECT due to circular inheritance.
 *
 * Violation: A class cannot inherit from itself, either directly or indirectly.
 * This creates a recursive inheritance relationship that is logically invalid
 * and prohibited by the C++ standard.
 *
 * Compiler Error: Typically produces "incomplete type" or "cyclic inheritance"
 * error messages because Derived is being used in its own base specifier list
 * before its definition is complete.
 */

/*
 * (b): class Derived : private Base { ... };
 * CORRECT syntactically and semantically.
 *
 * Validity: Private inheritance is a valid access specifier in C++.
 * It establishes an "is-implemented-in-terms-of" relationship rather than
 * an "is-a" relationship typical of public inheritance.
 *
 * Implications:
 * - All public and protected members of Base become private in Derived
 * - The inheritance relationship is not visible to users of Derived
 * - Useful for composition-like relationships with implementation reuse
 */

/*
 * DECLARATION (c): class Derived : public Base;
 * INCORRECT due to improper syntax.
 *
 * Violation: This appears to be a forward declaration attempting to specify
 * inheritance, which is not allowed in C++. Forward declarations cannot
 * include base class specifications or access specifiers.
 *
 * Correct Usage:
 * - Forward declaration: class Derived;
 * - Full definition: class Derived : public Base { ... };
 *
 * The inheritance relationship must be specified in the complete class
 * definition, not in a forward declaration.
 */