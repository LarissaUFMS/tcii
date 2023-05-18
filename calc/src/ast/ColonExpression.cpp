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
// OVERVIEW: ColonExpression.cpp
// ========
// Source for colon expression.
//
// Author: Paulo Pagliosa
// Last revision: 15/05/2023

#include "ast/ColonExpression.h"

namespace calc::ast
{ // begin namespace calc::ast


/////////////////////////////////////////////////////////////////////
//
// ColonExpression implementation
// ===============
void
ColonExpression::resolve(Scope* scope)
//[]----------------------------------------------------[]
//|  Resolve                                             |
//[]----------------------------------------------------[]
{
  auto t1 = _e1->resolveVoid(scope);
  auto t3 = _e3->resolveVoid(scope);
  auto t2 = _e2->resolveVoid(scope);

  setResolvedType(t3 == Type::Float() ? t3 :
    t1 == t2 ? t1 : Type::Float());
}

Expression::Value
ColonExpression::eval(Frame* frame) const
//[]----------------------------------------------------[]
//|  Eval                                                |
//[]----------------------------------------------------[]
{
  auto v1 = _e1->eval(frame);
  auto v3 = _e3->eval(frame);
  auto v2 = _e2->eval(frame);

  return Value::range(v1, v2, v3);
}

} // end namespace calc::ast
