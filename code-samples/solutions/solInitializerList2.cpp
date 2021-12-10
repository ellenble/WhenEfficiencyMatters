#include <cstdio>

struct UInit {
  UInit() { printf("default\n"); }

  UInit(const UInit&) { printf("copy ctor\n"); }
};

int main()
{
  UInit a;
  UInit b(a);
  UInit c{a};
}
