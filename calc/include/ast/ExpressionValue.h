#ifndef __ExpressionValue_h
#define __ExpressionValue_h

#include "ast/Expression.h"
#include "Matrix.h"
#include <variant>

using IntMatrix = Matrix<int>;
using FloatMatrix = Matrix<float>;

namespace calc
{ // begin namespace calc

//
// Forward definition
//
class Writer;

namespace ast
{ // begin namespace ast


/////////////////////////////////////////////////////////////////////
//
// Expression::Value: expression value class
// =================
class Expression::Value
{
public:
  Value():
	  _type{ Type::Float() },
	  _value{ FloatMatrix() }
  {}
  Value(int v):
	  _type{ Type::Float() }
  {
	  float vCast = static_cast<float>(v);
	  _value = FloatMatrix( vCast);
	
  }
  Value(float v):
	  _type{ Type::Float() },
	  _value{ FloatMatrix(v) }
  {}

  Type* type() const
  {
    return _type;
  }

  Value castTo(const Type* other) const
  {
	  if (this->type() == other)
	  {
		  return *this;
	  }

	  Value temp;
	  *temp._type = *other;

	  if (other == Type::Int())
	  {
		  temp._value = castTo<float, int>();
	  }
	  else
	  {
		  temp._value = castTo<int, float>();
	  }
	  return temp;
  }

  Value operator +(const Value& other) const
  {
	  typesEqual(other);

	  Value temp;
	  temp._type = _type;
	  if (_type == Type::Float())
	  {
		  temp._value = std::get<FloatMatrix>(_value) + std::get<FloatMatrix>(other._value);
	  }
	  else
	  {
		  temp._value = std::get<IntMatrix>(_value) + std::get<IntMatrix>(other._value);
	  }

	  return temp;
  }

  Value operator -(const Value& other) const
  {
	  typesEqual(other);

	  Value temp;
	  temp._type = _type;
	  if (_type == Type::Float())
	  {
		  temp._value = std::get<FloatMatrix>(_value) - std::get<FloatMatrix>(other._value);
	  }
	  else
	  {
		  temp._value = std::get<IntMatrix>(_value) - std::get<IntMatrix>(other._value);
	  }

	  return temp;
  }

  Value operator *(const Value& other) const
  {
	  typesEqual(other);

	  Value temp;
	  temp._type = _type;
	  if (_type == Type::Float())
	  {
		  temp._value = std::get<FloatMatrix>(_value) * std::get<FloatMatrix>(other._value);
	  }
	  else
	  {
		  temp._value = std::get<IntMatrix>(_value) * std::get<IntMatrix>(other._value);
	  }

	  return temp;
  }
  //refazer operador / ..................................................................//
  Value operator /(const Value& other) const// refazer ...............................
  {
	  typesEqual(other);

	  Value temp;
	  temp._type = _type;
	  if (_type == Type::Float())
	  {
		  temp._value = std::get<FloatMatrix>(_value) * std::get<FloatMatrix>(other._value);
	  }
	  else
	  {
		  temp._value = std::get<IntMatrix>(_value) * std::get<IntMatrix>(other._value);
	  }

	  return temp;
  } // refazer ...............................

  Value operator -() const
  {
	  Value temp;
	  temp._type = _type;
	  if (_type == Type::Float())
	  {
		  temp._value = - std::get<FloatMatrix>(_value);
	  }
	  else
	  {
		  temp._value = - std::get<IntMatrix>(_value);
	  }

	  return temp;
  }

  Value size() const
  {
	  Value temp;
	  temp._type = Type::Int();

	  size_t m, n;
	  if (_type == Type::Float())
	  {
		  m = std::get<FloatMatrix>(_value).rows();
		  n = std::get<FloatMatrix>(_value).cols();
	  }
	  else
	  {
		  m = std::get<IntMatrix>(_value).rows();
		  n = std::get<IntMatrix>(_value).cols();
	  }
	  temp._value = IntMatrix{ m, n };
	  return temp;
  }

  Value transpose() const
  {
	  Value temp;
	  temp._type = _type;

	  if (_type == Type::Float())
	  {
		  temp._value = std::get<FloatMatrix>(_value).transpose();
	  }
	  else
	  {
		  temp._value = std::get<IntMatrix>(_value).transpose();
	  }
	  return temp;
  }

  Value horzcat(const Value& other) const
  {
	  Value temp;
	  temp._type = _type;

	  typesEqual(other);
	  if (_type == Type::Float())
	  {
		  temp._value = std::get<FloatMatrix>(_value).horzcat(std::get<FloatMatrix>(other._value));
	  }
	  else
	  {
		  temp._value = std::get<IntMatrix>(_value).horzcat(std::get<IntMatrix>(other._value));
	  }
	  return temp;
  }

  Value vertcat(const Value& other) const
  {
	  Value temp;
	  temp._type = _type;

	  typesEqual(other);
	  if (_type == Type::Float())
	  {
		  temp._value = std::get<FloatMatrix>(_value).vertcat(std::get<FloatMatrix>(other._value));
	  }
	  else
	  {
		  temp._value = std::get<IntMatrix>(_value).vertcat(std::get<IntMatrix>(other._value));
	  }
	  return temp;
  }

  Value operator ()(const Value&) const;
  Value operator ()(const Value&, const Value&) const;

  Value rows(const Value&) const;
  Value cols(const Value&) const;
  Value vector() const;

  void set(const Value&, const Value&);
  void set(const Value&, const Value&, const Value&);
  void setRows(const Value&, const Value&);
  void setCols(const Value&, const Value&);
  void setVector(const Value&);

  void write(Writer& w) const;

  static Value colon(const Value&, const Value&, const Value&);

private:
  Type* _type;
  std::variant<FloatMatrix, IntMatrix> _value;

  /*template <typename T> Value(const Matrix<T>&);

  //Size valueSize() const;
  template <typename T> Matrix<T> castTo() const;
  Value block(const IntMatrix&, const IntMatrix&) const;
  template <template <typename T> typename Op> Value bop(const Value&) const;

  template <typename T> Matrix<T>& get();
  void setBlock(const IntMatrix&, const IntMatrix&, const Value&);*/

  template <typename Tcurrent, typename Tcast>
  Matrix<Tcast> castTo() const
  {
	  Matrix<Tcurrent> tempCurrent = std::get<Matrix<Tcurrent>>(this->_value);
	  Tcurrent* dataCurrentPtr = tempCurrent.data();
	  auto m = tempCurrent.rows();
	  auto n = tempCurrent.cols();
	  Tcast* dataCast{};
	  for (size_t s = m * n, i{}; i < s; ++i)
		  dataCast[i] = static_cast<Tcast>(dataCurrentPtr[i]);
	  Matrix<Tcast> tempCast(m, n, dataCast);
	  return tempCast;
  }

  template <typename T>
  Matrix<T> get() const
  {
    return const_cast<Value*>(this)->get<T>();
  }

  void typesEqual(const Value& other) const
  {
	  if (_type != other._type)
	  {
		  other.castTo(Type::Float());
		  castTo(Type::Float());
	  }
  }

}; // Expression::Value

} // end namespace ast

} // end namespace calc

#endif // __ExpressionValue_h
