#include <cstdio>
#include <vector>

int square(int a)
{
  return a * a;
}

int main()
{
  std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for(auto it = v.begin(); it != v.end(); ++it) {
    const auto sqrt = square(*it);
    printf("[%d] %d\n", *it, sqrt);
  }
}
