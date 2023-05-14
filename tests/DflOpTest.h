#ifndef __DflOpTest_h
#define __DflOpTest_h

#include <cstdio>

namespace test
{ // begin namespace test

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

class W
{
public:
  ~W() = default;
  W() = default;
  W(const W&) = default;
  W& operator =(const W&) = default;
  W(W&&) = default;
  W& operator =(W&&) = default;

  void print(const char* s) const
  {
    printf("**W:%s**\n", s);
  }

private:
  Aux _aux;

}; // X

inline auto
fw()
{
  W temp;

  temp.print("temp");
  return temp;
}

} // end namespace test

inline void
dflOpTest()
{
  puts("**\nSPECIAL MEMBER FUNCTIONS");

  using namespace test;

  W w1;

  w1.print("w1");

  auto w2 = w1;

  w2.print("w2");

  auto w3 = fw();

  w3.print("w3");
  w1 = w2;
  w1.print("w1");
  w2 = w3;
  w2.print("w2");
}

#endif // __DflOpTest_h
