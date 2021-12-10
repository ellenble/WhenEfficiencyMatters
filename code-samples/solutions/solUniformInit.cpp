#include <cstdio>

struct Foo {
  int  x;
  char c;
};

class Bar {
public:
  Bar(int x, char c)
  : mX{x}
  , mC{c}
  {}

private:
  int  mX;
  char mC;
};

int main()
{
  Foo f{3, static_cast<char>(250)};
  Bar b{2, 'x'};

  int x{4};

  for(int i{0}; i < 10; ++i) { printf("i=%d\n", i); }
}
