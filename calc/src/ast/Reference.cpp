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
// OVERVIEW: Reference.cpp
// ========
// Source file for reference.
//
// Author: Paulo Pagliosa
// Last revision: 18/05/2023

#include "ast/ColonAtom.h"
#include "Frame.h"
#include "ProblemReporter.h"

namespace calc::ast
{ // begin namespace calc::ast

inline auto
isColonAtom(Expression* e)
{
  return dynamic_cast<ColonAtom*>(e) != nullptr;
}


/////////////////////////////////////////////////////////////////////
//
// Reference implementation
// =========
void
Reference::resolve(Scope* scope)
//[]----------------------------------------------------[]
//|  Resolve                                             |
//[]----------------------------------------------------[]
{
  auto hasColonAtom = false;

  for (auto a : _arguments)
  {
    a->resolveVoid(scope);
    hasColonAtom |= isColonAtom(a);
  }
  if ((variable = scope->lookupVariable(_name)) != nullptr)
  {
    if (_arguments.size() > 2)
      problemReporter.tooManyArguments(scope, this);
  }
  else if (_place == LHS || hasColonAtom)
    problemReporter.undefinedVariable(scope, this);
  else if ((function = scope->lookupFunction(_name)) == nullptr)
    problemReporter.undefinedVariableOrFunction(scope, this);
  else if (_arguments.size() > function->parameters().size())
    problemReporter.tooManyArguments(scope, this);
  setResolvedType(Type::Variant());
}

Expression::Value
Reference::eval(Frame* frame) const
//[]----------------------------------------------------[]
//|  Eval                                                |
//[]----------------------------------------------------[]
{
  // TODO
  return Value{};
}

} // end namespace calc::ast
