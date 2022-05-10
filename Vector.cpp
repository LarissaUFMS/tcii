#include "Vector.h"

namespace math
{ // begin namespace math

VectorBody*
VectorBody::null()
{
  static VectorBody _null;

  if (_null.useCount() == 0)
    VectorBody::makeUse(&_null);
  return &_null;
}

VectorBody::VectorBody(const VectorBody& other):
  VectorBody{other._n}
{
  for (auto i = 0; i < _n; ++i)
    _data[i] = other._data[i];
}

VectorBody*
VectorBody::add(const VectorBody* b) const
{
  if (_n != b->_n)
    ; // TODO

  auto c = new VectorBody{_n};

  for (auto i = 0; i < _n; ++i)
    c->_data[i] = _data[i] + b->_data[i];
  return c;
}

VectorBody*
VectorBody::sub(const VectorBody* b) const
{
  if (_n != b->_n)
    ; // TODO

  auto c = new VectorBody{_n};

  for (auto i = 0; i < _n; ++i)
    c->_data[i] = _data[i] - b->_data[i];
  return c;
}

VectorBody*
VectorBody::mul(float s) const
{
  auto c = new VectorBody{_n};

  for (auto i = 0; i < _n; ++i)
    c->_data[i] = _data[i] * s;
  return c;
}

void
VectorBody::add_eq(const VectorBody* b)
{
  if (_n != b->_n)
    ; // TODO
  for (auto i = 0; i < _n; ++i)
    _data[i] += b->_data[i];
}

void
VectorBody::sub_eq(const VectorBody* b)
{
  if (_n != b->_n)
    ; // TODO
  for (auto i = 0; i < _n; ++i)
    _data[i] -= b->_data[i];
}

void
VectorBody::mul_eq(float s)
{
  for (auto i = 0; i < _n; ++i)
    _data[i] *= s;
}

} // end namespace math