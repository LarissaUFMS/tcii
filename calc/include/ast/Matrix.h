#ifndef __Matrix_h
#define __Matrix_h

#include "math/Vector.h"
#include "parser/ErrorHandler.h"
#include "ast/ExpressionValue.h"
#include <iostream>


enum class MatrixIndexType
{
    Row,
    Col
};

inline auto
matrixIndexOutOfRange(MatrixIndexType it, int i, size_t n)
{
    calc::ErrorHandler errorHandler;
    errorHandler.error(0, "Matrix index out of range: "
        "%s %d not in [0,%llu)",
        it == MatrixIndexType::Row ? "row" : "column", i, n);
}

inline auto
matrixDimensionMustAgree(size_t m1, size_t n1, size_t m2, size_t n2)
{
    calc::ErrorHandler errorHandler;
    errorHandler.error(0, "Matrix dimensions must agree: "
        "(%llu,%llu), (%llu,%llu)", m1, n1, m2, n2);
}

template <typename T>
class Matrix
{
    friend class calc::ast::Expression::Value;
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

    Matrix(float v)
    {
        _data = new float[1] {v};
    }

    Matrix(int v)
    {
        _data = new int[1] { v };
    }

    Matrix(size_t m, size_t n) :
        _m{ m }, _n{ n }
    {
        _data = new T[m * n];
    }

    Matrix(size_t m, size_t n, T* data) :
        _m{ m }, _n{ n }
    {
        _data = new T[_m * _n];
        for (size_t s = _m * _n, i{}; i < s; ++i)
            _data[i] = data[i];
    }

    Matrix(const Matrix&);
    Matrix(Matrix&&) noexcept;

    ~Matrix()
    {
        delete[]_data;
    }

    auto rows() const
    {
        return _m;
    }

    auto cols() const
    {
        return _n;
    }

    Matrix<T> operator ()(const Matrix<int>& m) const
    {
        if (m.cols() > 1)
        {
            Matrix<T> matrix(1LLU, m.cols());
            for (int i{}; i < m.cols(); ++i)
            {
                matrix._data[i] = _data[m.data()[i]];
            }
            return matrix;
        }
        Matrix<T> matrix(_data[m.data()[0]]);
        return matrix;
    }

    Matrix<T> operator ()(const Matrix<int>& m1, const Matrix<int>& m2) const
    {
        Matrix matrix{ m1.cols(), m2.cols() };
        if (m1.cols() == 0 && m1.data() != nullptr)
            matrix._m = 1LLU;
        if (m2.cols() == 0 && m2.data() != nullptr)
            matrix._n = 1LLU;
        if (m1.cols() * m2.cols() != matrix._m * matrix._n)
            matrix._data = new T[matrix._m * matrix._n];

        for (size_t i{}; i < matrix._m; ++i)
        {
            for (size_t j{}; j < matrix._n; ++j)
                matrix._data[i * matrix._n + j] = (*this)._data[(m1.data()[i] * _n + m2.data()[j])];
        }
        return matrix;
    }

    T& operator ()(int i, int j)
    {
#ifdef _DEBUG
        if (i < 0 || i >= _m)
            matrixIndexOutOfRange(MatrixIndexType::Row, i, _m);
        if (j < 0 || j >= _n)
            matrixIndexOutOfRange(MatrixIndexType::Col, j, _n);
#endif // _DEBUG

        return _data[i * _n + j];
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

    template<typename U>
    Matrix<T> operator /(const Matrix<U>&) const;

    Matrix operator +(const T&) const;
    Matrix operator -(const T&) const;

    template<typename U>
    Matrix operator *(const U&) const;

    Matrix operator -() const;

    Matrix<T> set(const Matrix<int>& m1, const Matrix<T>& m2)
    {
        if (m1.cols() > 1)
        {
            for (int i{}; i < m1.cols(); ++i)
            {
                if (m2.cols() < 2)
                    _data[m1.data()[i]] = m2.data()[0];
                else
                    _data[m1.data()[i]] = m2.data()[i];
            }
            return *this;
        }
        _data[m1.data()[0]] = m2.data()[0];
        return *this;
    }

    template <typename Tcast>
    Matrix<Tcast> castTo() const;

    Matrix transpose() const;
    Matrix horzcat(const Matrix&) const;
    Matrix vertcat(const Matrix&) const;

    Matrix horzcat(const T&) const;
    //Matrix vertcat(const T&) const;

    Matrix& row(int i) const;
    Matrix& col(int j) const;

    T* data() const;

    static Matrix colon(const Matrix&, const Matrix&, const Matrix&);

private:
    size_t _m{};
    size_t _n{};
    T* _data{ nullptr };

}; // end class Matrix


using IntMatrix = Matrix<int>;
using FloatMatrix = Matrix<float>;

template <typename T>
Matrix<T>::Matrix(const Matrix& other) :
    Matrix{ other._m, other._n }
{
    for (size_t s = _m * _n, i = 0; i < s; ++i)
        _data[i] = other._data[i];
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
{
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
    if (_m != other._m || _n != other._n)
    {
        delete[]_data;
        _m = other._m;
        _n = other._n;
        _data = new T[_m * _n];
    }
    for (size_t s = _m * _n, i{}; i < s; ++i)
        _data[i] = other._data[i];
    return *this;
}

template <typename T>
Matrix<T>&
Matrix<T>::operator =(Matrix&& other) noexcept
{
    delete[]_data;
    _m = other._m;
    _n = other._n;
    _data = other._data;
    other._m = other._n = 0;
    other._data = nullptr;
    return *this;
}

template <typename T>
Matrix<T>&
Matrix<T>::operator +=(const Matrix& b)
{
    *this = std::move(*this + b);
    return *this;
}

template <typename T>
Matrix<T>&
Matrix<T>::operator -=(const Matrix& b)
{
    *this = std::move(*this - b);
    return *this;
}

template <typename T>
Matrix<T>&
Matrix<T>::operator *=(const Matrix& b)
{
    *this = std::move(*this * b);
    return *this;
}

template <typename T>
Matrix<T>&
Matrix<T>::operator *=(const T& t)
{
    for (size_t s = _m * _n, i{}; i < s; ++i)
        _data[i] = _data[i] * t;
    return *this;
}

template <typename T>
Matrix<T>
Matrix<T>::operator +(const Matrix& b) const
{
    if (b._m == 0)
    {
        if (_m == 0)
            return Matrix{ _data[0] + b._data[0] };
        return *this + b._data[0];
    }
    if (_m == 0)
        return b + _data[0];

#ifdef _DEBUG
    if (_m != b._m || _n != b._n)
        matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif // _DEBUG

    Matrix c{ _m, _n };

    for (size_t s = _m * _n, i{}; i < s; ++i)
        c._data[i] = _data[i] + b._data[i];
    return c;
}

template <typename T>
Matrix<T>
Matrix<T>::operator -(const Matrix& b) const
{
    if (b._m == 0)
    {
        if (_m == 0)
            return Matrix{ _data[0] - b._data[0] };
        return *this - b._data[0];
    }
    if (_m == 0)
        return b - _data[0];
#ifdef _DEBUG
    if (_m != b._m || _n != b._n)
        matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif // _DEBUG

    Matrix c{ _m, _n };

    for (size_t s = _m * _n, i{}; i < s; ++i)
        c._data[i] = _data[i] - b._data[i];
    return c;
}

template <typename T>
Matrix<T>
Matrix<T>::operator *(const Matrix& b) const
{
    if (b._m == 0)
    {
        if (_m == 0)
            return Matrix{ _data[0] * b._data[0] };
        return *this * b._data[0];
    }
    if (_m == 0)
        return b * _data[0];

#ifdef _DEBUG
    if (_n != b._m)
        matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif //_DEBUG

    Matrix c(_m, b._n);

    for (size_t i = 0; i < _m; i++)
    {
        for (size_t j = 0; j < b._n; j++)
        {
            c._data[i * c._n + j] = 0;
            for (size_t k = 0; k < _n; k++)
                c._data[i * b._n + j] += _data[i * _n + k] * b._data[k * b._n + j];
        }
    }
    return c;
}

template <typename T>
Matrix<T>
Matrix<T>::operator +(const T& t) const
{
    Matrix c{ _m, _n };

    for (size_t s = _m * _n, i{}; i < s; ++i)
        c._data[i] = _data[i] + t;
    return c;
}

template <typename T>
Matrix<T>
Matrix<T>::operator -(const T& t) const
{
    return *this + (-t);
}

template <typename T>
Matrix<T>
Matrix<T>::operator -() const
{
    Matrix c{ _m, _n };

    for (size_t s = _m * _n, i{}; i < s; ++i)
        c._data[i] = -_data[i];
    return c;
}

template<typename T>
template<typename U>
inline Matrix<T> Matrix<T>::operator/(const Matrix<U>& d) const
{
    if (_m == 0)
    {
        T v = _data[0] / static_cast<T>(d.data()[0]);
        Matrix<T> m{v};
        return m;
    }

    return *this * (1 / d.data()[0]);
}

template<typename T>
template<typename U>
inline Matrix<T> Matrix<T>::operator*(const U& u) const
{
    Matrix<T> c{ _m, _n };

    for (size_t s = _m * _n, i{}; i < s; ++i)
        c._data[i] = static_cast<T>(_data[i] * u);

    return c;
}

template<typename T>
template<typename Tcast>
inline Matrix<Tcast> Matrix<T>::castTo() const
{
    if (_m == 0 && _data != nullptr)
    {
        Tcast tempCast{ static_cast<Tcast>(data()[0]) };
        return tempCast;
    }
    Matrix<Tcast> tempCast(_m, _n);
    for (size_t s = _m * _n, i{}; i < s; ++i)
        tempCast.data()[i] = static_cast<Tcast>(data()[i]);

    return tempCast;
}


template <typename T>
Matrix<T>
Matrix<T>::transpose() const
{
    Matrix c{ _n, _m };

    for (size_t i = 0; i < _m; ++i)
    {
        for (size_t j = 0; j < _n; ++j)
            c._data[_m * j + i] = _data[_n * i + j];
    }
    return c;
}

template <typename T>
Matrix<T>
Matrix<T>::horzcat(const Matrix& b) const
{
    if (b._m == 0)
        return this->horzcat(b._data[0]);
    if (_m == 0)
        return b;
#ifdef _DEBUG
    if (_m != b._m)
        matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif //_DEBUG

    Matrix c{ _m, _n + b._n };
    size_t r, k;

    for (size_t i{}; i < _m; ++i)
    {
        r = i * (_n + b._n);
        k = i * _n;
        for (size_t j{}; j < _n; ++j)
        {
            c._data[r + j] = _data[k + j];
        }

        r = i * (_n + b._n) + _n;
        k = i * b._n;
        for (size_t j{}; j < b._n; ++j)
        {
            c._data[r + j] = b._data[k + j];
        }
    }
    return c;
}

template <typename T>
Matrix<T>
Matrix<T>::vertcat(const Matrix& b) const
{
    if (_m == 0)
        return b;
#ifdef _DEBUG
    if (_n != b._n && _m != 0)
        matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif //_DEBUG

    Matrix<T> c(_m + b._m, b._n);

    for (size_t s = _m * _n, i{}; i < s; ++i)
        c._data[i] = _data[i];

    for (size_t s = b._m * b._n, i{}, k{ _m * _n }; i < s; ++i, ++k)
        c._data[k] = b._data[i];
    return c;
}

template <typename T>
Matrix<T>
Matrix<T>::horzcat(const T& b) const
{
    if (_m == 0)
    {
        T data[1] = { b };
        Matrix c{ 1, 1, data };
        return c;
    }
#ifdef _DEBUG
    if (_m != 1)
        matrixDimensionMustAgree(_m, _n, 1, 1);
#endif //_DEBUG

    Matrix c{ _m, _n + 1 };
    for (int i{}; i < _n; ++i)
        c._data[i] = _data[i];
    c._data[_n] = b;
    return c;
}

template<typename T>
Matrix<T>&
Matrix<T>::row(int row) const
{
    Matrix<T> c = Matrix<T>(1, _n);

    for (int i{}, r = row * _n; i < _n; ++i)
        c._data[i] = _data[r + i];

    return *c;
}

template<typename T>
Matrix<T>&
Matrix<T>::col(int col) const
{
    Matrix<T> c = Matrix<T>(1, _m);

    for (int j{}; j < _m; ++j)
        c._data[j] = _data[col + j * _n];

    return *c;
}

template <typename T>
void
Matrix<T>::iterate(IterFunc f) const
{
    Element e{};

    e.i = 0;
    for (int p = 0; e.i < _m; ++e.i)
        for (e.j = 0; e.j < _n; ++e.j)
        {
            e.value = _data[p++];
            f(e);
        }
}

template <typename T>
T*
Matrix<T>::data() const
{
    return _data;
}

template<typename T>
inline Matrix<T> Matrix<T>::colon(const Matrix& a, const Matrix& b, const Matrix& c)
{
    size_t n = size_t((b._data[0] - a._data[0]) / c._data[0]);

    Matrix<T> temp(1LLU, n + 1);

    for (int i{}; i <= n; ++i)
        temp._data[i] = a._data[0] + i * c._data[0];

    return temp;
}
#endif // __Matrix_h
