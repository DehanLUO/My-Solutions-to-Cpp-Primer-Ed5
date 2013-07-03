/*
 * Exercise 4.37: Rewrite each of the following old-style casts to use a named
 * cast:
 *     int i;  double d;  const string *ps;  char *pc;  void *pv;
 *     (a) pv = (void*)ps;
 *     (b) i = int(*pc);
 *     (c) pv = &d;
 *     (d) pc = (char*) pv;
 */

#include <string>  // std::string

int main() {
  // Variable declarations per
  int i;
  double d;
  const std::string *ps;
  char *pc;
  void *pv;

  // (a) pv = (void*)ps;
  // Old C-style cast → C++ named cast
  // Appropriate cast: const_cast would remove constness, but we need to convert
  // pointer type
  pv = const_cast<std::string *>(ps);  // Removes const
  pv = static_cast<void *>(
      const_cast<std::string *>(ps));  // Complete conversion

  // (b) i = int(*pc);
  // Old C-style cast → C++ named cast
  // Appropriate cast: static_cast for well-defined conversions
  i = static_cast<int>(*pc);

  // (c) pv = &d;
  // No cast needed in original, but if explicit cast desired:
  pv = static_cast<void *>(&d);

  // (d) pc = (char*) pv;
  // Old C-style cast → C++ named cast
  // Appropriate cast: reinterpret_cast for pointer-to-pointer conversions
  pc = reinterpret_cast<char *>(pv);

  return 0;
}
