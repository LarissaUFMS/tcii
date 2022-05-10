#include "Matrix.h"
#include <iostream>

void
print(const math::Matrix::Element& e)
{
  printf("(%d,%d)=%f\n", e.i, e.j, e.value);
}

void
vectorTest()
{
  using namespace math;

  auto u = Vector{10};

  for (int i = 0; i < u.size(); ++i)
    u(i) = float(i);

  auto c = u.clone();
  auto v = u;
  Vector q;

  q = u += c;
  for (int i = 0; i < q.size(); ++i)
    printf("q(%d)=%g\n", i, q(i));
  for (int i = 0; i < v.size(); ++i)
    printf("v(%d)=%g\n", i, v(i));
}

void
matrixTest()
{
  using namespace math;

  auto a = Matrix{3, 3};
  auto b = Matrix{3, 3};

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
  c.iterate(print);
}
