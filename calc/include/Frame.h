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
// OVERVIEW: Frame.h
// ========
// Class definition for execution frame.
//
// Author: Paulo Pagliosa
// Last revision: 16/05/2023

#ifndef __Frame_h
#define __Frame_h

#include "ast/ExpressionValue.h"
#include "symbol/Scope.h"

namespace calc
{ // begin namespace calc


/////////////////////////////////////////////////////////////////////
//
// FrameRecord: frame record class
// ===========
class FrameRecord: public Symbol
{
public:
  ast::Expression::Value value;

  FrameRecord(const String& name):
    Symbol{name},
    value{float{}}
  {
    // do nothing
  }

}; // FrameRecord


/////////////////////////////////////////////////////////////////////
//
// Frame: execution frame class
// =====
class Frame: public symbol::SymbolMap<FrameRecord>
{
public:
  Frame(Frame* parent, const Scope* scope):
    _parent{parent}
  {
    build(scope);
  }

  auto parent() const
  {
    return _parent;
  }

  virtual FrameRecord* findRecord(const String&) const;

protected:
  Frame* _parent;

  void build(const Scope*);

}; // Frame

} // end namespace calc

#endif // __Frame_h
