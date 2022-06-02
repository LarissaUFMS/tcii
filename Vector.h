#ifndef __Vector_h
#define __Vector_h

#include "Exception.h"
#include "SharedObject.h"

namespace math
{ // begin namespace math

inline auto
vectorDimensionMustAgree(size_t n1, size_t n2)
{
  util::error<std::logic_error>("Vector dimensions "
    "%llu and %llu must agree",
    n1,
    n2);
}

inline auto
vectorIndexOutOfRange()
{
  util::error<std::logic_error>("Vector index out of range");
}

template <typename T, size_t N> class Vector;

template <typename T>
class VectorBody: public util::SharedObject
{
public:
  void* operator new(size_t size, size_t n)
  {
    return ::operator new(size + n * sizeof(T));
  }

  void operator delete(void* ptr, size_t)
  {
    ::operator delete(ptr);
  }

  void operator delete(void* ptr)
  {
    ::operator delete(ptr);
  }

private:
  using body_type = VectorBody<T>;

  static auto New(size_t n)
  {
    return new (n) body_type{n};
  }

  VectorBody() = default;

  VectorBody(size_t n):
    _n{n}
  {
    _data = reinterpret_cast<T*>(this + 1);
  }

  VectorBody(const body_type&);

  auto clone() const
  {
    return new (_n) body_type{*this};
  }

  body_type* add(const body_type*) const;
  body_type* sub(const body_type*) const;
  body_type* mul(const T&) const;

  void add_eq(const body_type*);
  void sub_eq(const body_type*);
  void mul_eq(const T&);

private:
  size_t _n{};
  T* _data{};

  static body_type* null();

  friend Vector<T, 0>;

};  // VectorBody

template <typename T>
VectorBody<T>*
VectorBody<T>::null()
{
  static body_type _null;

  if (_null.useCount() == 0)
    body_type::makeUse(&_null);
  return &_null;
}

template <typename T>
VectorBody<T>::VectorBody(const body_type& other):
  VectorBody{other._n}
{
  for (auto i = 0; i < _n; ++i)
    _data[i] = other._data[i];
}

template <typename T>
VectorBody<T>*
VectorBody<T>::add(const body_type* b) const
{
  if (_n != b->_n)
    vectorDimensionMustAgree(_n, b->_n);

  auto c = New(_n);

  for (auto i = 0; i < _n; ++i)
    c->_data[i] = _data[i] + b->_data[i];
  return c;
}

template <typename T>
VectorBody<T>*
VectorBody<T>::sub(const body_type* b) const
{
  if (_n != b->_n)
    vectorDimensionMustAgree(_n, b->_n);

  auto c = New(_n);

  for (auto i = 0; i < _n; ++i)
    c->_data[i] = _data[i] - b->_data[i];
  return c;
}

template <typename T>
VectorBody<T>*
VectorBody<T>::mul(const T& s) const
{
  auto c = New(_n);

  for (auto i = 0; i < _n; ++i)
    c->_data[i] = _data[i] * s;
  return c;
}

template <typename T>
void
VectorBody<T>::add_eq(const body_type* b)
{
  if (_n != b->_n)
    vectorDimensionMustAgree(_n, b->_n);
  for (auto i = 0; i < _n; ++i)
    _data[i] += b->_data[i];
}

template <typename T>
void
VectorBody<T>::sub_eq(const body_type* b)
{
  if (_n != b->_n)
    vectorDimensionMustAgree(_n, b->_n);
  for (auto i = 0; i < _n; ++i)
    _data[i] -= b->_data[i];
}

template <typename T>
void
VectorBody<T>::mul_eq(const T& s)
{
  for (auto i = 0; i < _n; ++i)
    _data[i] *= s;
}

template <typename T>
class Vector<T, 0>
{
public:
  using vector_type = Vector<T, 0>;

  Vector():
    Vector{VectorBody<T>::null()}
  {
    // do nothing
  }

  Vector(int n):
    Vector{VectorBody<T>::New(n)}
  {
    // do nothing
  }

  Vector(const vector_type& other):
    Vector{other._body}
  {
    // do nothing
  }

  auto clone() const
  {
    return vector_type{_body->clone()};
  }

  auto size() const
  {
    return _body->_n;
  }

  auto operator ()(int i) const
  {
    if (i < 0 || i >= _body->_n)
      vectorIndexOutOfRange();
    return _body->_data[i];
  }

  auto& operator ()(int i)
  {
    if (i < 0 || i >= _body->_n)
      vectorIndexOutOfRange();
    checkCopyOnWrite();
    return _body->_data[i];
  }

  auto& operator =(const Vector& other)
  {
    _body = other._body;
    return *this;
  }

  auto operator +(const vector_type& b) const
  {
    return vector_type{_body->add(b._body)};
  }

  auto operator -(const vector_type& b) const
  {
    return vector_type{_body->sub(b._body)};
  }

  auto operator *(const T& s) const
  {
    return vector_type{_body->mul(s)};
  }

  auto& operator +=(const vector_type& b)
  {
    checkCopyOnWrite();
    _body->add_eq(b._body);
    return *this;
  }

  auto& operator -=(const vector_type& b)
  {
    checkCopyOnWrite();
    _body->sub_eq(b._body);
    return *this;
  }

  auto& operator *=(const T& s)
  {
    checkCopyOnWrite();
    _body->mul_eq(s);
    return *this;
  }

private:
  util::ObjectPtr<VectorBody<T>> _body;

  Vector(const VectorBody<T>* body):
    _body{body}
  {
    // do nothing
  }

  void checkCopyOnWrite()
  {
    if (_body->useCount() > 1)
      _body = _body->clone();
  }

};  // Vector

using VectorXf = Vector<float, 0>;

} // end namespace math

template <typename T, size_t N>
inline auto
operator *(const T& s, const math::Vector<T, N>& v)
{
  return v * s;
}

#endif // __Vector_h
