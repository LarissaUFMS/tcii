#ifndef __Matrix_h
#define __Matrix_h

#include "Vector.h"

namespace math
{ // begin namespace math

enum class IndexType
{
  Row,
  Col
};

auto
matrixIndexOutOfRange(IndexType it, int i, int n)
{
  util::error<std::logic_error>(
    "Matrix index out of range: %s %d not in [0,%d)",
    it == IndexType::Row ? "row" : "column",
    i,
    n);
}

class Matrix
{
public:
  struct Element
  {
    int i;
    int j;
    float value;
  };

  using IterFunc = void(const Element&);

  void iterate(IterFunc) const;

  Matrix() = default;

  Matrix(int m, int n)
  {
    _m = m;
    _n = n;
    _data = new float[m * n];
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
      matrixIndexOutOfRange(IndexType::Row, i, _m);
    if (j < 0 || j >= _n)
      matrixIndexOutOfRange(IndexType::Col, j, _n);
#endif
    return _data[i * _n + j];
  }

  auto operator ()(int i, int j) const
  {
    return const_cast<Matrix*>(this)->operator ()(i, j);
  }

  Matrix& operator =(const Matrix&);
  Matrix& operator =(Matrix&&) noexcept;

  Matrix operator +(const Matrix&) const;
  Matrix operator -(const Matrix&) const;
  Matrix operator *(const Matrix&) const;
  Matrix operator *(const VectorXf&) const;
  Matrix operator *(float) const;

  Matrix& operator +=(const Matrix&);
  Matrix& operator -=(const Matrix&);
  Matrix& operator *=(const Matrix&);
  Matrix& operator *=(const VectorXf&);
  Matrix& operator *=(float);

  Matrix transpose() const;

private:
  int _m{};
  int _n{};
  float* _data{};

}; // Matrix

} // end namespace math

inline auto
operator *(float s, const math::Matrix& m)
{
  return m * s;
}

#endif // __Matrix_h
