#ifndef __Vector_h
#define __Vector_h

#include "SharedObject.h"

namespace math
{ // begin namespace math

class Vector;

class VectorBody: public util::SharedObject
{
public:
  ~VectorBody()
  {
    delete []_data;
  }

private:
  VectorBody() = default;

  VectorBody(int n)
  {
    _n = n;
    _data = new float[n];
  }

  VectorBody(const VectorBody&);

  VectorBody* add(const VectorBody*) const;
  VectorBody* sub(const VectorBody*) const;
  VectorBody* mul(float) const;

  void add_eq(const VectorBody*);
  void sub_eq(const VectorBody*);
  void mul_eq(float);

private:
  int _n{};
  float* _data{};

  static VectorBody* null();

  friend Vector;

};  // VectorBody

class Vector
{
public:
  Vector():
    Vector{VectorBody::null()}
  {
    // do nothing
  }

  Vector(int n):
    Vector{new VectorBody{n}}
  {
    // do nothing
  }

  Vector(const Vector& other):
    Vector{other._body}
  {
    // do nothing
  }

  auto clone() const
  {
    return Vector{new VectorBody{*_body}};
  }

  auto size() const
  {
    return _body->_n;
  }

  auto operator ()(int i) const
  {
    if (i < 0 || i >= _body->_n)
      ; // TODO
    return _body->_data[i];
  }

  auto& operator ()(int i)
  {
    if (i < 0 || i >= _body->_n)
      ; // TODO
    return _body->_data[i];
  }

  auto& operator =(const Vector& other)
  {
    _body = other._body;
    return *this;
  }

  auto operator +(const Vector& b) const
  {
    return Vector{_body->add(b._body)};
  }

  auto operator -(const Vector& b) const
  {
    return Vector{_body->sub(b._body)};
  }

  auto operator *(float s) const
  {
    return Vector{_body->mul(s)};
  }

  auto& operator +=(const Vector& b)
  {
    _body->add_eq(b._body);
    return *this;
  }

  auto& operator -=(const Vector& b)
  {
    _body->sub_eq(b._body);
    return *this;
  }

  auto & operator *=(float s)
  {
    _body->mul_eq(s);
    return *this;
  }

private:
  util::ObjectPtr<VectorBody> _body;

  Vector(const VectorBody* body):
    _body{body}
  {
    // do nothing
  }

};  // Vector

} // end namespace math

inline auto
operator *(float s, const math::Vector& v)
{
  return v * s;
}

#endif // __Vector_h
