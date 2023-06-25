#ifndef __Matrix_h
#define __Matrix_h

#include "math/Vector.h"


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
        it == MatrixIndexType::Row ? "row" : "column", i, n);
}

inline auto
matrixDimensionMustAgree(size_t m1, size_t n1, size_t m2, size_t n2)
{
    util::error<std::logic_error>("Matrix dimensions must agree: "
        "(%llu,%llu), (%llu,%llu)", m1, n1, m2, n2);
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

    Matrix(float v):
        _m{1}, _n{1}
    {
        _data = new float{v};
    }

    Matrix(size_t m, size_t n):
        _m{m}, _n{n}
    {
        _data = new T[m * n];
    }

    Matrix(size_t m, size_t n, T* data):
        _m{m}, _n{n},
        _data{ data }
    {}

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
    Matrix operator *(const T&) const;

    Matrix operator -() const;

    //Matrix castTo();

    Matrix transpose() const;
    Matrix horzcat(const Matrix&) const;
    Matrix vertcat(const Matrix&) const;

    Matrix& row(int i) const;
    Matrix& col(int j) const;

    T* data() const;

private:
    size_t _m{};
    size_t _n{};
    T* _data{};

}; // end class Matrix

template <typename T>
Matrix<T>::Matrix(const Matrix& other) :
    Matrix{ other._m, other._n }
{
#ifdef _DEBUG
    puts("**Matrix copy ctor**");
#endif // _DEBUG
    for (size_t s = _m * _n, i = 0; i < s; ++i)
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
#ifdef _DEBUG
    puts("**Matrix move op**");
#endif // _DEBUG
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
#ifdef _DEBUG
    if (_m != b._n)
        matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif //_DEBUG

    Matrix c(_m, b._n);

    for (size_t i = 0; i < _m; i++)
    {
        for (size_t j = 0; j < b._n; j++)
        {
            for (size_t k = 0; k < _n; k++)
                c._data[i * b._n + j] += _data[i * _n + k] * b._data[k * b._n + j];
        }
    }
    return c;
}

template <typename T>
Matrix<T>
Matrix<T>::operator *(const T& t) const
{
    Matrix c{ _m, _n };

    for (size_t s = _m * _n, i{}; i < s; ++i)
        c._data[i] = _data[i] * t;
    return c;
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
#ifdef _DEBUG
    if (_m != b._n)
        matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif //_DEBUG

    Matrix c{_m, _n + b._n};
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
            c._data[r + j] = _data[k + j];
        }
    }
    return c;
}

template <typename T>
Matrix<T>
Matrix<T>::vertcat(const Matrix& b) const
{
#ifdef _DEBUG
    if (_n != b._n)
        matrixDimensionMustAgree(_m, _n, b._m, b._n);
#endif //_DEBUG

    Matrix<T> c(_m + b._m, _n);

    for (size_t s = _m * _n, i{}; i < s; ++i)
        c._data[i] = _data[i];

    for (size_t s = b._m * b._n, i{}, k{_m * _n}; i < s; ++i, ++k)
        c._data[i] = b._data[i];
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
    Element e;

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
#endif // __Matrix_h
