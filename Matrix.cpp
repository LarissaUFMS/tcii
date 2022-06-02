#include "Matrix.h"

namespace math
{ // begin namespace math

inline auto
matrixDimensionMustAgree(size_t m1, size_t n1, size_t m2, size_t n2)
{
  util::error<std::logic_error>("Matrix dimensions "
    "(%llu,%llu) and (%llu,%llu) must agree",
    m1, n1,
    m2, n2);
}

Matrix::Matrix(const Matrix& other):
  Matrix{other._m, other._n}
{
#ifdef _DEBUG
  puts("**Matrix copy ctor**");
#endif // _DEBUG
  for (auto s = _m * _n, i = 0; i < s; ++i)
    _data[i] = other._data[i];
}

Matrix::Matrix(Matrix&& other) noexcept:
  Matrix{other._m, other._n}
{
#ifdef _DEBUG
  puts("**Matrix move ctor**");
#endif // _DEBUG
  _data = other._data;
  other._m = other._n = 0;
  other._data = nullptr;
}

Matrix&
Matrix::operator =(const Matrix& other)
{
#ifdef _DEBUG
  puts("**Matrix copy op**");
#endif // _DEBUG
  if (_m != other._m || _n != other._n)
  {
    delete []_data;
    _m = other._m;
    _n = other._n;
    _data = new float[_m * _n];
  }
  for (auto s = _m * _n, i = 0; i < s; ++i)
    _data[i] = other._data[i];
  return *this;
}

Matrix&
Matrix::operator =(Matrix&& other) noexcept
{
#ifdef _DEBUG
  puts("**Matrix move op**");
#endif // _DEBUG
  delete []_data;
  _m = other._m;
  _n = other._n;
  _data = other._data;
  other._m = other._n = 0;
  other._data = nullptr;
  return *this;
}

Matrix
Matrix::operator +(const Matrix& b) const
{
  if (_m != b._m || _n != b._n)
    matrixDimensionMustAgree(_m, _n, b._m, b._n);

  Matrix c{_m, _n};

  for (auto s = _m * _n, i = 0; i < s; ++i)
    c._data[i] = _data[i] + b._data[i];
  return c;
}

Matrix&
Matrix::operator +=(const Matrix& b)
{
  if (_m != b._m || _n != b._n)
    matrixDimensionMustAgree(_m, _n, b._m, b._n);
  for (auto s = _m * _n, i = 0; i < s; ++i)
    _data[i] += b._data[i];
  return *this;
}

void
Matrix::iterate(IterFunc f) const
{
  Element e;

  e.i = 0;
  for (int p = 0; e.i < _m; ++e.i)
    for (e.j = 0; e.j < _n; ++e.j)
    {
      e.value = _data[p++];
      f(e);
    }
}

} // end namespace math
