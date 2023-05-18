//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2010, 2023 Paulo Pagliosa.                        |
//|                                                                 |
//| This software is provided 'as-is', without any express or       |
//| implied warranty. In no event will the authors be held liable   |
//| for any damages arising from the use of this software.          |
//|                                                                 |
//| Permission is granted to anyone to use this software for any    |
//| purpose, including commercial applications, and to alter it and |
//| redistribute it freely, subject to the following restrictions:  |
//|                                                                 |
//| 1. The origin of this software must not be misrepresented; you  |
//| must not claim that you wrote the original software. If you use |
//| this software in a product, an acknowledgment in the product    |
//| documentation would be appreciated but is not required.         |
//|                                                                 |
//| 2. Altered source versions must be plainly marked as such, and  |
//| must not be misrepresented as being the original software.      |
//|                                                                 |
//| 3. This notice may not be removed or altered from any source    |
//| distribution.                                                   |
//|                                                                 |
//[]---------------------------------------------------------------[]
//
// OVERVIEW: MatrixExpression.cpp
// ========
// Sourrce file for matrix expression.
//
// Author: Paulo Pagliosa
// Last revision: 15/05/2023

#include "ast/MatrixExpression.h"

namespace calc::ast
{ // begin namespace calc::ast


/////////////////////////////////////////////////////////////////////
//
// MatrixRow implementation
// =========
void
MatrixRow::resolve(Scope* scope)
//[]----------------------------------------------------[]
//|  Resolve                                             |
//[]----------------------------------------------------[]
{
  setResolvedType(ExpressionList::resolveVoid(scope));
}

Expression::Value
MatrixRow::eval(Frame* frame) const
//[]----------------------------------------------------[]
//|  Eval                                                |
//[]----------------------------------------------------[]
{
  Value value;

  for (auto e : *this)
    value = value.horzcat(e->eval(frame));
  return value;
}


/////////////////////////////////////////////////////////////////////
//
// MatrixExpression implementation
// ================
void
MatrixExpression::resolve(Scope* scope)
//[]----------------------------------------------------[]
//|  Resolve                                             |
//[]----------------------------------------------------[]
{
  auto type = Type::Int();

  for (auto r : _rows)
  {
    r->resolve(scope);
    if (r->resolvedType() == Type::Float())
      type = Type::Float();
  }
  setResolvedType(type);
}

Expression::Value
MatrixExpression::eval(Frame* frame) const
//[]----------------------------------------------------[]
//|  Eval                                                |
//[]----------------------------------------------------[]
{
  Value value;

  for (auto r : _rows)
    value = value.vertcat(r->eval(frame));
  return value;
}

} // end namespace calc::ast
