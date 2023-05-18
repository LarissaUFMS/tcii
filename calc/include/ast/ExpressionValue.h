#ifndef __ExpressionValue_h
#define __ExpressionValue_h

#include "ast/Expression.h"

namespace calc
{ // begin namespace calc

//
// Forward definitions
//
namespace symbol { class Type; }
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
  Value()
  {
    // TODO
  }

  Value(int)
  {
    // TODO
  }

  Value(float)
  {
    // TODO
  }

  Value castTo(const Type*) const
  {
    // TODO
    return {};
  }

  Value operator +(const Value&) const
  {
    // TODO
    return {};
  }

  Value operator -(const Value&) const
  {
    // TODO
    return {};
  }

  Value operator *(const Value&) const
  {
    // TODO
    return {};
  }

  Value operator /(const Value&) const
  {
    // TODO
    return {};
  }

  Value operator -() const
  {
    // TODO
    return {};
  }

  Value size() const
  {
    // TODO
    return {};
  }

  Value transpose() const
  {
    // TODO
    return {};
  }

  Value horzcat(const Value&) const
  {
    // TODO
    return {};
  }

  Value vertcat(const Value&) const
  {
    // TODO
    return {};
  }

  static Value range(const Value&, const Value&, const Value&)
  {
    return {};
  }

  void write(Writer&) const
  {
    // TODO
    printf("OK");
  }

}; // Expression::Value

} // end namespace ast

} // end namespace calc

#endif // __ExpressionValue_h
