#ifndef __ExpressionValue_h
#define __ExpressionValue_h

#include "ast/Expression.h"
#include "Matrix.h"
#include <variant>
#include <iostream>

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
  {
#ifdef _DEBUG
	  puts("** Value()**");
#endif // _DEBUG
  }
  Value(int v):
	  _type{ Type::Float() }
  {
#ifdef _DEBUG
	  puts("** Value(int)**");
#endif // _DEBUG
	  _value = static_cast<float>(v);
	
  }
  Value(float v) :
	  _type{ Type::Float() },
	  _value { v } 
  {
#ifdef _DEBUG
	  puts("** Value(float)**");
#endif // _DEBUG}
  }

  Type* type() const
  {
#ifdef _DEBUG
	  puts("** Value type()**");
#endif // _DEBUG
    return _type;
  }

  Value castTo(const Type* other) const
  {
#ifdef _DEBUG
	  puts("** Value castTo**");
#endif // _DEBUG
	  if (this->type() == other)
	  {
		  return *this;
	  }

	  Value temp;
	  *temp._type = *other;

	  if (other == Type::Int())
	  {
		  if (auto v = std::get_if<int>(&_value))
			  temp._value = static_cast<float>(*v);
		  else
			  temp._value = castTo<float, int>();
	  }
	  else
	  {
		  if (auto v = std::get_if<float>(&_value))
			  temp._value = static_cast<int>(*v);
		  else
			  temp._value = castTo<int, float>();
	  }
	  return temp;
  }

  Value operator +(const Value& other) const
  {
#ifdef _DEBUG
	  puts("** Value operator +(Value&)**");
#endif // _DEBUG
	  typesEqual(other);

	  Value temp;
	  temp._type = _type;
	  if (_type == Type::Float())
	  {
		  if (auto v1 = std::get_if<float>(&_value))
		  {
			  if (auto v2 = std::get_if<float>(&other._value))
				  temp._value = *v1 + *v2;
			  else
				  temp._value = std::get<FloatMatrix>(other._value) + *v1;
		  }
		  else if (auto v1 = std::get_if<float>(&other._value))
		  {
			  if (auto v2 = std::get_if<float>(&_value))
				  temp._value = *v1 + *v2;
			  else
				  temp._value = std::get<FloatMatrix>(_value) + *v1;
		  }
		  else
			temp._value = std::get<FloatMatrix>(_value) + std::get<FloatMatrix>(other._value);
	  }
	  else
	  {
		  if (auto v1 = std::get_if<int>(&_value))
		  {
			  if (auto v2 = std::get_if<int>(&other._value))
				  temp._value = *v1 + *v2;
			  else
				  temp._value = std::get<IntMatrix>(other._value) + *v1;
		  }
		  else if (auto v1 = std::get_if<int>(&other._value))
		  {
			  if (auto v2 = std::get_if<int>(&_value))
				  temp._value = *v1 + *v2;
			  else
				  temp._value = std::get<IntMatrix>(_value) + *v1;
		  }
		  else
			temp._value = std::get<IntMatrix>(_value) + std::get<IntMatrix>(other._value);
	  }

	  return temp;
  }

  Value operator -(const Value& other) const
  {
#ifdef _DEBUG
	  puts("** Value operator -(Value&)**");
#endif // _DEBUG
	  typesEqual(other);

	  Value temp;
	  temp._type = _type;
	  if (_type == Type::Float())
	  {
		  if (auto v1 = std::get_if<float>(&_value))
		  {
			  if (auto v2 = std::get_if<float>(&other._value))
				  temp._value = *v1 - *v2;
			  else
				  temp._value = std::get<FloatMatrix>(other._value) - *v1;
		  }
		  else if (auto v1 = std::get_if<float>(&other._value))
		  {
			  if (auto v2 = std::get_if<float>(&_value))
				  temp._value = *v1 - *v2;
			  else
				  temp._value = std::get<FloatMatrix>(_value) - *v1;
		  }
		  else
			  temp._value = std::get<FloatMatrix>(_value) - std::get<FloatMatrix>(other._value);
	  }
	  else
	  {
		  if (auto v1 = std::get_if<int>(&_value))
		  {
			  if (auto v2 = std::get_if<int>(&other._value))
				  temp._value = *v1 - *v2;
			  else
				  temp._value = std::get<IntMatrix>(other._value) - *v1;
		  }
		  else if (auto v1 = std::get_if<int>(&other._value))
		  {
			  if (auto v2 = std::get_if<int>(&_value))
				  temp._value = *v1 - *v2;
			  else
				  temp._value = std::get<IntMatrix>(_value) - *v1;
		  }
		  else
			  temp._value = std::get<IntMatrix>(_value) - std::get<IntMatrix>(other._value);
	  }

	  return temp;
  }

  Value operator *(const Value& other) const
  {
#ifdef _DEBUG
	  puts("** Value operator *(Value&)**");
#endif // _DEBUG
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

	  int m, n;
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

	  int data[2]{m, n};
	  temp._value = IntMatrix{ static_cast<size_t>(1), static_cast < size_t>(2), data};

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
#ifdef _DEBUG
	  puts("** horzcat(Value&)**");
#endif // _DEBUG

	  Value temp;
	  temp._type = _type;
	  typesEqual(other);
	  if (_type == Type::Float())
	  {
		  if (auto v = get_if<float>(&other._value))
			  temp._value = std::get<FloatMatrix>(_value).horzcat(*v);
		  else
			temp._value = std::get<FloatMatrix>(_value).horzcat(std::get<FloatMatrix>(other._value));
	  }
	  else
	  {
		  if (auto v = get_if<int>(&other._value))
			  temp._value = std::get<IntMatrix>(_value).horzcat(*v);
		  else
			  temp._value = std::get<IntMatrix>(_value).horzcat(std::get<IntMatrix>(other._value));
	  }
	  return temp;
  }

  Value vertcat(const Value& other) const
  {
#ifdef _DEBUG
	  puts("** Value vertcat(Value&)**");
#endif // _DEBUG

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

  //refazer métodos abaixo / ..................................................................//
  Value operator ()(const Value&) const
  {
	  return *this;
  }
  Value operator ()(const Value&, const Value&) const
  {
	  return *this;
  }

  Value rows(const Value&) const
  {
	  return *this;
  }
  Value cols(const Value&) const
  {
	  return *this;
  }
  Value vector() const
  {
	  return *this;
  }
  void set(const Value&, const Value&)
  {
	  ;
  }
  void set(const Value&, const Value&, const Value&) 
  {
	  ;
  }
  void setRows(const Value&, const Value&)
  {
	  ;
  }
  void setCols(const Value&, const Value&)
  {
	  ;
  }
  void setVector(const Value&)
  {
	  ;
  }

  void write(Writer& w) const
  {
	  if (auto v = std::get_if<int>(&_value))
	  {
		  std::cout << *v;
	  }
	  else if (auto v = std::get_if<float>(&_value))
	  {
		  std::cout << *v;
	  }
	  else if (auto floatMatrix = std::get_if<FloatMatrix>(&this->_value))
	  {
		  auto m = floatMatrix->rows();
		  auto n = floatMatrix->cols();

		  if (m == 0)
		  {
			  std::cout << "[]";
			  return;
		  }

		  for (size_t i{}; i < m; ++i)
		  {
			  auto aux = i* n;
			  for (size_t j{}; j < n; ++j)
				  std::cout << floatMatrix->_data[ aux + j] << ',' ;
			  std::cout << '\n';
		  }
	  }
	  else
	  {
		  auto intMatrix = std::get_if<IntMatrix>(&this->_value);

		  auto m = intMatrix->rows();
		  auto n = intMatrix->cols();

		  for (size_t i{}; i < m; ++i)
		  {
			  auto aux = i * n;
			  for (size_t j{}; j < n; ++j)
				  std::cout << intMatrix->_data[aux + j] << ',';
			  std::cout << '\n';
		  }
	  }
  }

  static Value colon(const Value& a, const Value& b, const Value& c)
  {
	  return a;
  }
private:
  Type* _type;
  std::variant<FloatMatrix, IntMatrix, int, float> _value;

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
	  Tcast* dataCast = new Tcast[m * n];
	  for (size_t s = m * n, i{}; i < s; ++i)
		  dataCast[i] = static_cast<Tcast>(dataCurrentPtr[i]);
	  Matrix<Tcast> tempCast(m, n, dataCast);
	  std::cout << "Type of Tcast: " << typeid(Tcast).name() << std::endl;
	  std::cout << "Type of dataCast: " << typeid(*dataCast).name() << std::endl;
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
