#include <cstdio>
#include <initializer_list>

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

void List(std::initializer_list<int> list)
{
  for(const int* i{list.begin()}; i != list.end(); ++i) { printf("%d\n", *i); }
}

int main()
{
  Foo f{2, static_cast<char>(250)};
  Bar b{2, 'x'};

  int x{4};

  for(int i{0}; i < 10; ++i) { printf("i=%d\n", i); }

  List({1, 2, 3, 4});
}
