#include <cstdio>
#include <initializer_list>

struct UInit {
  UInit() { printf("default\n"); }

  UInit(const UInit&) { printf("copy ctor\n"); }

  UInit(const std::initializer_list<UInit>&) { printf("initializer list\n"); }
};

int main()
{
  UInit a;
  UInit b(a);  // copy ctor
  UInit c{a};  // copy ctor (init. list element) + initializer list!!!
}
