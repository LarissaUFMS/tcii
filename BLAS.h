#ifndef __BLAS_h
#define __BLAS_h

#include <cassert>
#include <concepts>

namespace math
{ // begin namespace math

namespace concepts
{ // begin namespace concepts

template <typename T>
concept Vector = std::floating_point<typename T::value_type> &&
requires (const T& x, T& y, size_t n)
{
  typename T::value_type;
  T(n);
  {x.size()} -> std::convertible_to<size_t>;
  {x(n)} -> std::same_as<typename T::value_type>;
  {y(n)} -> std::same_as<typename T::value_type&>;
} &&
  std::copy_constructible<T>;

} // end namespace concepts

template <typename Vector>
  requires concepts::Vector<Vector>
void
print1(const Vector& x)
{
  auto n = x.size();

  for (decltype(n) i = 0; i < n; ++i)
    printf("%g ", x(i));
}

template <typename Vector>
void
print2(const Vector& x)
  requires concepts::Vector<Vector>
{
  auto n = x.size();

  for (decltype(n) i = 0; i < n; ++i)
    printf("%g ", x(i));
}

template <concepts::Vector Vector>
void
print3(const Vector& x)
{
  auto n = x.size();

  for (decltype(n) i = 0; i < n; ++i)
    printf("%g ", x(i));
}

void
print4(const concepts::Vector auto& x)
{
  auto n = x.size();

  for (decltype(n) i = 0; i < n; ++i)
    printf("%g ", x(i));
}

template <concepts::Vector Vector>
class BLAS
{
public:
  using real = typename Vector::value_type;

  Vector& aspx(Vector& x, const Vector& y, real s);
  Vector aspx(const Vector& x, const Vector& y, real s);

}; // BLAS

template <concepts::Vector Vector>
Vector&
BLAS<Vector>::aspx(Vector& x, const Vector& y, real s)
{
  auto n = x.size();

  assert(n == y.size());
  for (decltype(n) i = 0; i < n; ++i)
    x(i) += y(i) * s;
  return x;
}

template <concepts::Vector Vector>
Vector
BLAS<Vector>::aspx(const Vector& x, const Vector& y, real s)
{
  auto n = x.size();

  assert(n == y.size());

  Vector c{n};

  for (decltype(n) i = 0; i < n; ++i)
    c(i) = x(i) + y(i) * s;
  return c;
}

class V
{
public:
  using value_type = float;

  V(int n);
  float operator ()(int i) const;
  float& operator ()(int i);
  int size() const;
};

void
testBLAS()
{
  BLAS<V> b;
  auto x = V{10};
  const auto y = V{10};

  b.aspx(x, y, 3);
}

} // end namespace math

#endif // __BLAS_h
