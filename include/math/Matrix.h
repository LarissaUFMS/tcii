#ifndef __Matrix_h
#define __Matrix_h

#include "math/Vector.h"
#include <cstdio>

// An *academic* example of generic dynamic matrix by Paulo Pagliosa

/*
The template class Matrix below *is not* designed for efficiency and
its use in a real-world program is not encouraged. The purpose of
this example is just to demonstrate some C++ features such as
exception throwing, operator overloading, and copy/move operations.
*/

namespace math
{ // begin namespace math

enum class MatrixIndexType
{
  Row,
  Col
};

inline auto
matrixIndexOutOfRange(MatrixIndexType it, int i, size_t n)
{
  util::error<std::logic_error>("Matrix index out of range: "
    "%s %d not in [0,%llu)",
    it == MatrixIndexType::Row ? "row" : "column",
    i,
    n);
}

inline auto
matrixDimensionMustAgree(size_t m1, size_t n1, size_t m2, size_t n2)
{
  util::error<std::logic_error>("Matrix dimensions must agree: "
    "(%llu,%llu), (%llu,%llu)",
    m1, n1,
    m2, n2);
}

template <typename T>
class Matrix
{
public:
  using value_type = T;

  struct Element
  {
    int i;
    int j;
    T value;
  };

  using IterFunc = void(const Element&);

  void iterate(IterFunc) const;

  Matrix() = default;

  Matrix(size_t m, size_t n)
  {
    _m = m;
    _n = n;
    _data = new T[m * n];
  }

  Matrix(const Matrix&);
  Matrix(Matrix&&) noexcept;

  ~Matrix()
  {
    delete []_data;
  }

  auto rows() const
  {
    return _m;
  }

  auto cols() const
  {
    return _n;
  }

  auto& operator ()(int i, int j)
  {
#ifdef _DEBUG
    if (i < 0 || i >= _m)
      matrixIndexOutOfRange(MatrixIndexType::Row, i, _m);
    if (j < 0 || j >= _n)
      matrixIndexOutOfRange(MatrixIndexType::Col, j, _n);
#endif // _DEBUG
    return _data[i * _n + j];
  }

  auto operator ()(int i, int j) const
  {
    return const_cast<Matrix*>(this)->operator ()(i, j);
  }

  Matrix& operator =(const Matrix&);
  Matrix& operator =(Matrix&&) noexcept;

  Matrix& operator +=(const Matrix&);
  Matrix& operator -=(const Matrix&);
  Matrix& operator *=(const Matrix&);
  Matrix& operator *=(const T&);

  Matrix operator +(const Matrix&) const;
  Matrix operator -(const Matrix&) const;
  Matrix operator *(const Matrix&) const;
  Vector<T> operator *(const Vector<T>&) const;
  Matrix operator *(const T&) const;

  Matrix transpose() const;

private:
  size_t _m{};
  size_t _n{};
  T* _data{};

}; // Matrix

template <typename T>
Matrix<T>::Matrix(const Matrix& other):
  Matrix{other._m, other._n}
{
#ifdef _DEBUG
  puts("**Matrix copy ctor**");
#endif // _DEBUG
  for (auto s = _m * _n, i = 0; i < s; ++i)
    _data[i] = other._data[i];
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
{
#ifdef _DEBUG
  puts("**Matrix move ctor**");
#endif // _DEBUG
  _m = other._m;
  _n = other._n;
  _data = other._data;
  other._m = other._n = 0;
  other._data = nullptr;
}

template <typename T>
Matrix<T>&
Matrix<T>::operator =(const Matrix& other)
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
  for (size_t s = _m * _n, i{}; i < s; ++i)
    _data[i] = other._data[i];
  return *this;
}

template <typename T>
Matrix<T>&
Matrix<T>::operator =(Matrix&& other) noexcept
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

template <typename T>
Matrix<T>
Matrix<T>::operator +(const Matrix& b) const
{
#ifdef _DEBUG
  if (_m != b._m || _n != b._n)
    matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif // _DEBUG

  Matrix c{_m, _n};

  for (size_t s = _m * _n, i{}; i < s; ++i)
    c._data[i] = _data[i] + b._data[i];
  return c;
}

template <typename T>
Matrix<T>&
Matrix<T>::operator +=(const Matrix& b)
{
#ifdef _DEBUG
  if (_m != b._m || _n != b._n)
    matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif // _DEBUG
  for (size_t s = _m * _n, i{}; i < s; ++i)
    _data[i] += b._data[i];
  return *this;
}

// **Exercise: implement here the other matrix ops

template <typename T>
void
Matrix<T>::iterate(IterFunc f) const
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

template <typename T>
inline auto
operator *(const T& s, const math::Matrix<T>& m)
{
  return m * s;
}

#endif // __Matrix_h
