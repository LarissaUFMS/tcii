#ifndef __ExpressionValue_h
#define __ExpressionValue_h

#include "ast/Expression.h"
#include "Matrix.h"
#include <variant>
#include <iostream>
#include <cmath>

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
			Value() :
				_type{ Type::Float() },
				_value{ FloatMatrix() }
			{}

			Value(int v) :
				_type{ Type::Float() },
				_value{ FloatMatrix{ static_cast<float>(v) } }
			{}

			Value(float v) :
				_type{ Type::Float() },
				_value{ FloatMatrix{ v } }
			{}

			template <typename T> Value(const Matrix<T>& m)
			{
				static_assert(std::is_same<T, int>::value || std::is_same<T, float>::value);

				if (std::is_same<T, int>::value)
					_type = Type::Int();
				else
					_type = Type::Float();

				_value = m;
			}

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
					temp._value = std::get<FloatMatrix>(_value).castTo<int>();
				else
					temp._value = std::get<IntMatrix>(_value).castTo<float>();

				return temp;
			}

			Value operator +(const Value& other) const
			{
				typesEqual(other);

				Value temp;
				temp._type = _type;

				if (_type == Type::Float())
					temp._value = std::get<FloatMatrix>(_value) + std::get<FloatMatrix>(other._value);

				else
					temp._value = std::get<IntMatrix>(_value) + std::get<IntMatrix>(other._value);

				return temp;
			}

			Value operator -(const Value& other) const
			{
				typesEqual(other);

				Value temp;
				temp._type = _type;

				if (_type == Type::Float())
					temp._value = std::get<FloatMatrix>(_value) - std::get<FloatMatrix>(other._value);

				else
					temp._value = std::get<IntMatrix>(_value) - std::get<IntMatrix>(other._value);

				return temp;
			}

			Value operator *(const Value& other) const
			{
				typesEqual(other);
				Value temp;
				temp._type = _type;

				if (_type == Type::Float())
					temp._value = std::get<FloatMatrix>(_value) * std::get<FloatMatrix>(other._value);

				else
					temp._value = std::get<IntMatrix>(_value) * std::get<IntMatrix>(other._value);

				return temp;
			}

			Value operator /(const Value& other) const// refazer ...............................
			{
				Value temp;
				temp._type = _type;
				temp._value = std::visit<std::variant<FloatMatrix, IntMatrix>>([](auto&& arg1, auto&& arg2) {
					return arg1 / arg2;
					}, _value, other._value);
				return temp;
			} // refazer ...............................

			Value operator -() const
			{
				Value temp;
				temp._type = _type;

				temp._value = std::visit<std::variant<FloatMatrix, IntMatrix>>([](auto&& arg) {
					return -arg;
					}, _value);

				return temp;
			}

			Value size() const
			{
				Value temp;
				temp._type = Type::Int();

				//#ifdef _DEBUG
				//	  if (_value.index() == 2 || _value.index() == 3)
				//	  {
				//		  calc::ErrorHandler errorHandler;
				//		  errorHandler.error(0, "This is a real number.");
				//	  }
				//#endif // _DEBUG

				size_t m, n;

				temp._value = std::visit([&](auto&& arg) {
					m = arg.rows();
					n = arg.cols();
					int data[2]{ int(m), int(n) };
					return IntMatrix{ 1LLU, 2LLU, data };
					}, _value);

				return temp;
			}

			Value transpose() const
			{
				Value temp;
				temp._type = _type;

				temp._value = std::visit<std::variant<FloatMatrix, IntMatrix>>([](auto&& arg) {
					return arg.transpose();
					}, _value);

				return temp;
			}

			Value horzcat(const Value& other) const
			{

				typesEqual(other);

				Value temp;
				temp._type = _type;

				if (_type == Type::Float())
					temp._value = std::get<FloatMatrix>(_value).horzcat(std::get<FloatMatrix>(other._value));

				else
					temp._value = std::get<IntMatrix>(_value).horzcat(std::get<IntMatrix>(other._value));

				return temp;
			}

			Value vertcat(const Value& other) const
			{
				Value temp;
				temp._type = _type;
				typesEqual(other);

				if (_type == Type::Float())
					temp._value = std::get<FloatMatrix>(_value).vertcat(std::get<FloatMatrix>(other._value));

				else
					temp._value = std::get<IntMatrix>(_value).vertcat(std::get<IntMatrix>(other._value));

				return temp;
			}

			Value operator ()(const Value& other) const
			{
				Value temp;
				temp._type = _type;
				temp._value = std::visit<std::variant<FloatMatrix, IntMatrix>>([&other](auto&& arg) {
					return arg(std::get<IntMatrix>((other.castTo(Type::Int())._value)));
					}, _value);

				return temp;
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
				std::visit([](auto&& arg) {
					auto m = arg.rows();
					auto n = arg.cols();
					if (m == 0 && arg._data != nullptr)
						std::cout << arg._data[0] << '\n';
					else if (m == 0)
						std::cout << "[] \n";
					else
					{
						std::cout << "Matrix: \n";
						for (size_t i{}; i < m; ++i)
						{
							auto aux = i * n;
							for (size_t j{}; j < n; ++j)
								std::cout << arg._data[aux + j] << ' ';
							std::cout << '\n';
						}
					}
					}, _value);
			}

			static Value colon(const Value& a, const Value& b, const Value& c)
			{
				Value temp;
				temp._type = a._type;
				if (a._type == Type::Float())
					temp._value = FloatMatrix::colon(std::get<FloatMatrix>(a._value), std::get<FloatMatrix>(b._value), std::get<FloatMatrix>(c._value));
				else
					temp._value = IntMatrix::colon(std::get<IntMatrix>(a._value), std::get<IntMatrix>(b._value), std::get<IntMatrix>(c._value));
				return temp;
			}


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

			/*template <typename Tcurrent, typename Tcast>
			Matrix<Tcast> castTo() const
			{
				Matrix<Tcurrent> tempCurrent{std::get<Matrix<Tcurrent>>(this->_value)};
				Tcurrent* dataCurrentPtr = tempCurrent.data();
				auto m = tempCurrent.rows();
				auto n = tempCurrent.cols();
				if (m == 0 && dataCurrentPtr != nullptr)
				{
					Matrix<Tcast> tempCast{static_cast<Tcast>(dataCurrentPtr[0])};
					return tempCast;
				}
				Tcast* dataCast = new Tcast[m * n];
				for (size_t s = m * n, i{}; i < s; ++i)
					dataCast[i] = static_cast<Tcast>(dataCurrentPtr[i]);
				Matrix<Tcast> tempCast(m, n, dataCast);
				std::cout << "Type of Tcast: " << typeid(Tcast).name() << std::endl;
				std::cout << "Type of dataCast: " << typeid(*dataCast).name() << std::endl;
				return tempCast;
			}*/

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
