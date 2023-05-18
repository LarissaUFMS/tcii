#include <iostream>
#include <iomanip>
#include <limits>
#include <typeinfo>
#include <type_traits>

namespace test
{ // begin namespace test

template <typename T>
inline constexpr void
printTypeInfo()
{
  using namespace std;

  cout << "Type: " << typeid(T).name() << '\n';
  cout << "Size: " << sizeof(T) << '\n';
}

template <typename T>
inline constexpr void
printTypeInfo(T value)
{
  using namespace std;

  printTypeInfo<T>();
  if constexpr (is_arithmetic_v<T>)
  {
    cout << "Min:  " << numeric_limits<T>::min() << '\n';
    cout << "Max:  " << numeric_limits<T>::max() << '\n';
    cout << "Val:  " << value << '\n';
  }
}

inline void
numericTypeTest()
{
  puts("\n**NUMERIC TYPES");
  printTypeInfo<bool>();
  printTypeInfo<char>();
  printTypeInfo<signed char>();
  printTypeInfo<unsigned char>();
  printTypeInfo<short>();
  printTypeInfo<unsigned short>();
  printTypeInfo<int>();
  printTypeInfo<unsigned int>();
  printTypeInfo<long>();
  printTypeInfo<unsigned long>();
  printTypeInfo<long long>();
  printTypeInfo<unsigned long long>();
  printTypeInfo<float>();
  printTypeInfo<double>();
  printTypeInfo<long double>();

  bool b = true;
  char c = 'c';
  signed char sc = 'c';
  unsigned char uc = 63U;
  short s = 1;
  unsigned short us = 1U;
  int i = 1;
  unsigned int ui = 1U;
  long l = 1L;
  unsigned long ul = 1UL;
  long long ll = 1LL;
  unsigned long long ull = 1ULL;
  float f = 3.14F;
  double d = 314.0e-2;
  long double ld = 3.14L;

  puts("\n**NUMERIC LITERALS");
  printTypeInfo(b);
  printTypeInfo(c);
  printTypeInfo(sc);
  printTypeInfo(uc);
  printTypeInfo(s);
  printTypeInfo(us);
  printTypeInfo(i);
  printTypeInfo(ui);
  printTypeInfo(l);
  printTypeInfo(ul);
  printTypeInfo(ll);
  printTypeInfo(ull);
  printTypeInfo(f);
  printTypeInfo(d);
  printTypeInfo(ld);
}

inline void
structTypeTest()
{
  puts("\n**STRUCT INITIALIZATION");

  struct B
  {
    int a;
    int b;
  };

  B b = {1, 2};

  struct C
  {
    int a;
    B b;
  };

  C c = {1, {2, 3}};

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

  struct Y
  {
    D::X x;
    int a;
  };

  printTypeInfo<B>();
  printTypeInfo<C>();
  printTypeInfo<D>();
  printTypeInfo<Y>();
}

using uint = unsigned;

inline void
f(int a[10])
{
  puts("int[10] decays to int*:");
  printTypeInfo(a);
}

inline void
f(int a[][2])
{
  puts("int[][2] decays to int(*)[2]:");
  printTypeInfo(a);
}

inline void
arrayTest()
{
  puts("\n**ARRAY INITIALIZATION");

  using IA10 = int[10];

  IA10 ia10_1;
  int* p = ia10_1; // decays to int*

  *p = 1; // (p[0] = 1) == (ia10_1[0] = 1)

  int ia10_2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int ia3_1[3] = {1, 2, 3};
  int ia3_2[3] = {1};

  using IA2x3 = int[2][3];

  IA2x3 ia2x3_1;
  auto q = ia2x3_1; // decays to int(*)[3]

  *q[0] = 1; // (q[0][0] = 1) == (ia2x3_1[0][0] = 1)

  int ia3x2_1[][2] = {1, 2, 3, 4, 5};
  int ia3x2_2[][2] = {{1,2},{3,4},{5}};

  f(ia10_1);
  f(ia3x2_1);

  using IntTable = uint[]; // incomplete type

  IntTable f1 = {1, 2};
  IntTable f2 = {1, 2, 3};
}

// Func is a function, not a function pointer (int(*)(uint))
using Func = uint(uint);

inline uint
f(uint a) // f is a Func
{
  return a;
}

inline void
funcTest(Func f)
{
  puts("\n**FUNCTION AS FUNCTION PARAMETER");
  puts("Func decays to int(*)(uint):");
  printTypeInfo(f);
  f(2); // (*f)(2);
}

} // begin namespace test

inline void
typeTest()
{
  using namespace test;

  numericTypeTest();
  structTypeTest();
  arrayTest();
  funcTest(f);
}
