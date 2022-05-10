#include "Matrix.h"

namespace math
{ // begin namespace math

Matrix::Matrix(const Matrix& other):
  Matrix{other._m, other._n}
{
  for (auto s = _m * _n, i = 0; i < s; ++i)
    _data[i] = other._data[i];
}

Matrix&
Matrix::operator =(const Matrix& other)
{
  if (_m != other._m || _n != other._n)
  {
    delete[]_data;
    _m = other._m;
    _n = other._n;
    _data = new float[_m * _n];
  }
  for (auto s = _m * _n, i = 0; i < s; ++i)
    _data[i] = other._data[i];
  return *this;
}

Matrix
Matrix::operator +(const Matrix& b) const
{
  if (_m != b._m || _n != b._n)
    ; // TODO

  Matrix c{_m, _n};

  for (auto s = _m * _n, i = 0; i < s; ++i)
    c._data[i] = _data[i] + b._data[i];
  return c;
}

Matrix&
Matrix::operator +=(const Matrix& b)
{
  if (_m != b._m || _n != b._n)
    ; // TODO
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
