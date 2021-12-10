#include <cstdio>
#include <type_traits>

template<typename T, typename... Args>
T add(const T& arg, const Args&... args)
{
  if constexpr(sizeof...(args) > 0) {
    return arg + add(args...);
  } else {
    return arg;
  }
}

int main()
{
  printf("%d\n", add(2, 3, 4));

  printf("%d\n", add(2));
}
