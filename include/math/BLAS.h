#ifndef __BLAS_h
#define __BLAS_h

#include <cassert>
#include <concepts>

namespace math
{ // begin namespace math

template <typename T>
concept FloatVector = std::floating_point<typename T::value_type> &&
requires (const T& x, T& y, size_t n)
{
  typename T::value_type;
  T(n);
  {x.size()} -> std::convertible_to<size_t>;
  {x(n)} -> std::same_as<typename T::value_type>;
  {y(n)} -> std::same_as<typename T::value_type&>;
} &&
  std::copy_constructible<T>;

template <FloatVector Vector>
class BLAS
{
public:
  using real = typename Vector::value_type;

  // y += ax
  Vector& axpy(Vector& y, const Vector& x, real a);

}; // BLAS

template <FloatVector Vector>
Vector&
BLAS<Vector>::axpy(Vector& y, const Vector& x, real a)
{
  auto n = x.size();

  assert(n == y.size());
  for (int i{}; i < n; ++i)
    y(i) += x(i) * a;
  return y;
}

} // end namespace math

#endif // __BLAS_h
