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
// OVERVIEW: FunctionDeclaration.cpp
// ========
// Source file for function declaration.
//
// Author: Paulo Pagliosa
// Last revision: 17/05/2023

#include "ast/FunctionDeclaration.h"

namespace calc::ast
{ // begin namespace calc::ast


/////////////////////////////////////////////////////////////////////
//
// FunctionDeclaration implementation
// ===================
  void
    FunctionDeclaration::resolve(Scope* scope)
    //[]----------------------------------------------------[]
    //|  Resolve                                             |
    //[]----------------------------------------------------[]
  {
    // checa se as variaveis tem nomes diferentes

    auto param_itr_i = _parameters.begin();
    auto param_itr_j = _parameters.begin();
    auto param_end = _parameters.end();
    auto cmp = param_itr_i->name();
    bool invalid_variable = false;


    for (; param_itr_i != param_end && !invalid_variable; param_itr_i++)
    {
      for (param_itr_j = param_itr_i; param_itr_j != param_end; param_itr_j++)
      {
        if (cmp == param_itr_j->name())
        {
          invalid_variable = true;
          break;
        }
      }
    }

    if (invalid_variable)
    {
      // o que fazer quando tem variavel com nome repetido
    }

    // checa se ja existe fun��o com mesmo nome

    if (scope->lookupFunction(_name) != nullptr)
    {
      // se existir, sobrescreve(como??)

    }

    (void)scope;
  }

  Statement::JumpCode
    FunctionDeclaration::execute(Frame* frame) const
    //[]----------------------------------------------------[]
    //|  Execute                                             |
    //[]----------------------------------------------------[]
  {
    return JumpCode::NEXT;
  }

} // end namespace calc::ast
