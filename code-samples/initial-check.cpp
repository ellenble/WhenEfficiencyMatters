static constexpr unsigned long REQUIRED = 201103L;

#include <cstdio>

#if defined(_MSVC_LANG)
#define CPP_STD _MSVC_LANG
#elif defined(__cplusplus)
#define CPP_STD __cplusplus
#else
#error("unknown compiler")
#endif

#if defined(_MSC_VER)
#define not !
#endif

static bool Check(const char* std, unsigned long value)
{
  const static unsigned long STD = CPP_STD;

  printf(" - C++%s: ", std);

  if(STD >= value) {
    printf(" [OK]\n");
  } else {
    if(REQUIRED >= value) {
      printf(" [!!!FAILED!!!]\n");
      return false;

    } else {
      printf(" [FAILED]\n");
    }
  }

  return true;
}

int main()
{
  printf("Supported:\n");

  const bool failed =
    not Check("11", 201103L) || not Check("14", 201402L) || not Check("17", 201703L) || not Check("20", 202002L);

  printf("\nOverall: %s\n", failed ? "UNSUPPORTED" : "READY");

  return failed ? 1 : 0;
}