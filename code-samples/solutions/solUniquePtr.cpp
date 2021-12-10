#include <memory>

struct Foo {
  Foo(int) {}
  void method() {}
};

void someMethod(Foo* m) {}

int main()
{
  std::unique_ptr<Foo> ptr1{std::make_unique<Foo>(2)};

  // use a method from Foo
  ptr1->method();

  // get a raw pointer back
  someMethod(ptr1.get());

  // move the ressource
  std::unique_ptr<Foo> ptr2{std::move(ptr1)};

  // assign a new value
  ptr1.reset(new Foo{3});
  // better
  ptr1 = std::make_unique<Foo>(3);

  // clear the unique_ptr
  ptr1.reset();
}
