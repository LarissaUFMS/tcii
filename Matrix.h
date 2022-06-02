#ifndef __Matrix_h
#define __Matrix_h

#include "Vector.h"

namespace math
{ // begin namespace math

inline auto
matrixIndexOutOfRange()
{
  util::error<std::logic_error>("Matrix index out of range");
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

  auto operator ()(int i, int j) const
  {
    if (i < 0 || i >= _m || j < 0 || j >= _n)
      matrixIndexOutOfRange();
    return _data[i * _n + j];
  }

  auto& operator ()(int i, int j)
  {
    if (i < 0 || i >= _m || j < 0 || j >= _n)
      matrixIndexOutOfRange();
    return _data[i * _n + j];
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
