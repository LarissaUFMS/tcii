#include "math/BLAS.h"
#include "math/Matrix.h"

namespace test
{ // namespace test

template <typename Vector>
  requires math::FloatVector<Vector>
inline void
print1(const Vector& x)
{
  for (int i{}; i < x.size(); ++i)
    printf("%g ", x(i));
  putchar('\n');
}

template <typename Vector>
inline void
print2(const Vector& x)
  requires math::FloatVector<Vector>
{
  print1(x);
}

template <math::FloatVector Vector>
inline void
print3(const Vector& x)
{
  print1(x);
}

inline void
print4(const math::FloatVector auto& x)
{
  print1(x);
}

} // end namespace test

inline void
blasTest()
{
  puts("\n**CONCEPTS TEST");

  using namespace math;
  using namespace test;
  using Vectorf = Vector<float>;

  auto x = Vectorf{10};

  for (int i = 0; i < x.size(); ++i)
    x(i) = float(i);

  auto y = x;
  BLAS<Vectorf> blas;

  printf("axpy(y,x,3): ");
  print4(blas.axpy(y, x, 3));
}
