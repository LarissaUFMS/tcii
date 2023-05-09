#include <iostream>

template <typename T>
inline void
psize(const char* name)
{
  std::cout << "sizeof(" << name << "): " << sizeof(T) << '\n';
}

template <typename T>
inline void
psize(T value)
{
  std::cout << "sizeof " << value << ": " << sizeof value << '\n';
}

void
primitiveTypeTest()
{
  psize<bool>("bool");
  psize<char>("char");
  psize<double>("double");
  psize<float>("float");
  psize<long>("long");
  psize<long double>("long double");
  psize<long long>("long long");
  psize<int>("int");
  psize<short>("short");
  //psize<wchar_t>("wchar_t");

  bool b = true;
  char c = 'c';
  double d = 314.0e-2;
  float f = 3.14F;
  long l = 1L;
  long double ld = 3.14L;
  long long ll = 1LL;
  int i = 1;
  short s = 1;
  signed char sc = 'c';
  unsigned char uc = 127U;
  unsigned long ul = 1UL;
  unsigned long long ull = 1ULL;
  unsigned int ui = 1U;
  unsigned short us = 1U;
  wchar_t wc = L'c';

  psize(b);
  psize(c);
  psize(d);
  psize(f);
  psize(l);
  psize(ld);
  psize(ll);
  psize(i);
  psize(s);
  psize(sc);
  psize(ul);
  psize(ull);
  psize(ui);
  psize(us);
  //psize(wc);
}

void
structTypeTest()
{
  struct B
  {
    int a;
    int b;
  };

  B b = {1, 2};
  psize<B>("B");

  struct C
  {
    int a;
    B b;
  };

  C c = {1, {2, 3}};
  psize<C>("C");

  struct D
  {
    struct X
    {
      B b;
      C c;
    };

    C c;
    X x;
  };

  D d = {{1, {2, 3}}, {{4, 5}, {7, {7,8}}}};
  psize<D>("D");

  struct Y
  {
    D::X x;
    int a;
  };

  psize<Y>("Y");

}

using uint = unsigned;
using Func = uint(uint); // uint(*)(uint)

void
funcTest(Func f)
{
  f(2); // (*f)(2);
}

uint
f(uint a)
{
  return 1;
}

void
f(int a[10])
{

}

void
f(int a[][2])
{

}

void
arrayTest()
{
  using IA10 = int[10];

  IA10 ia10_1;
  int ia10_2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int ia3_1[3] = {1, 2, 3};
  int ia3_2[3] = {1};

  using IA2x3 = int[2][3];

  IA2x3 ia2x3_1;
  int ia2x3_2[2][3];
  int ia3x2_1[][2] = {1, 2, 3, 4, 5};
  int ia3x2_2[][2] = {{1,2},{3,4},{5}};

  int* p = ia10_1;
  auto q = ia10_1;

  *p = 1; // p[0] = 1; ia10_1[0] = 1;
  f(ia10_1);
  f(ia3x2_1);

  using IntTable = uint[]; // incomplete type

  IntTable f1 = {1, 2};
  IntTable f2 = {1, 2, 3};

  using Func = void(*)(uint);
  using FuncTable = Func[];
}


void
typeTest()
{
  //primitiveTypeTest();
  //structTypeTest();
  //funcTest(f);
  arrayTest();
}
