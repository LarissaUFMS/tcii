#include "math/Matrix.h"
#include <iostream>

namespace test
{ // bengin namespace test

inline void
print(const char* name, const math::Vector<float>& x)
{
  for (int i = 0; i < x.size(); ++i)
    printf("%s(%d)=%g\n", name, i, x(i));
}

void
print(const math::Matrix<float>::Element& e)
{
  printf("(%d,%d)=%g\n", e.i, e.j, e.value);
}

} // end namespace test

inline void
vectorTest()
{
  puts("**VECTOR TEST**");

  using namespace math;
  using namespace test;

  auto u = Vector<float>{10};

  for (int i = 0; i < u.size(); ++i)
    u(i) = float(i);

  auto c = u.clone();
  auto v = u;
  Vector<float> q;

  q = u += 2.0f * c;
  print("q", q);
  print("v", v);
  print("(q+[])", q + Vector<float>{}); // error
}

void
matrixTest()
{
  puts("**MATRIX TEST**");

  using namespace math;
  using namespace test;

  auto a = Matrix<float>{3, 3};
  auto b = Matrix<float>{3, 3};

  for (int i = 0; i < a.rows(); ++i)
    for (int j = 0; j < a.cols(); ++j)
      a(i, j) = b(i, j) = float(i + j);

  auto c = a + b;

  for (int i = 0; i < c.rows(); ++i)
  {
    for (int j = 0; j < c.cols(); ++j)
      std::cout << c(i, j) << ' ';
    std::cout << '\n';
  }
  // copy op
  a = c;
  c.iterate(print);
  // move op
  b = std::move(c);
  b.iterate(print);
}
