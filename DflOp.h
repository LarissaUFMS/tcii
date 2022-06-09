#ifndef __DflOp_h
#define __DflOp_h

#include <cstdio>

class Aux
{
public:
  ~Aux()
  {
    puts("**Dtor");
  }

  Aux()
  {
    puts("**Default ctor");
  }

  Aux(const Aux&)
  {
    puts("**Copy ctor");
  }

  Aux(Aux&&) noexcept
  {
    puts("**Move ctor");
  }

  Aux& operator =(const Aux&)
  {
    puts("**Copy op");
    return *this;
  }

  Aux& operator =(Aux&&) noexcept
  {
    puts("**Move op");
    return *this;
  }

}; // Aux

class X
{
public:
  ~X() = default;
  X() = default;
  X(const X&) = default;
  X& operator =(const X&) = default;
  X(X&&) = default;
  X& operator =(X&&) = default;

  void print(const char* s) const
  {
    printf("**X:%s**\n", s);
  }

private:
  Aux _aux;

}; // X

inline auto
fx()
{
  X temp;

  temp.print("temp");
  return temp;
}

inline void
testDflOp()
{
  X x1;

  x1.print("x1");

  auto x2 = x1;

  x2.print("x2");

  auto x3 = fx();

  x3.print("x3");
  x1 = x2;
  x1.print("x1");
  x2 = fx();
  x2.print("x2");
}

#endif // __DflOp_h
