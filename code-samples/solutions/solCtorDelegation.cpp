#undef USE_RECURSION
struct C {
  // 1: non-delegating constructor
  C(int) {}

  // 2: delegates to 1
  C()
  : C(42)
  {}

#ifdef USE_RECURSION
  // 3: ill-formed due to recursion with 4
  C(char c)
  : C(42.0)
  {}

  // 4: ill-formed due to recursion with 3
  C(double d)
  : C('a')
  {}
#endif
};

int main()
{
  C(2);
  C();
#ifdef USE_RECURSION
  C('a');
  C(3.5);
#endif
}
