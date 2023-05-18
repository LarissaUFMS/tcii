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
// OVERVIEW: Frame.cpp
// ========
// Source file for execution frame.
//
// Author: Paulo Pagliosa
// Last revision: 17/05/2023

#include "Frame.h"

namespace calc
{ // begin namespace calc


/////////////////////////////////////////////////////////////////////
//
// Frame implementation
// =====
FrameRecord*
Frame::findRecord(const String& name) const
//[]----------------------------------------------------[]
//|  Find record                                         |
//[]----------------------------------------------------[]
{
  auto r = find(name);
  return !r && _parent ? _parent->findRecord(name) : r;
}

void
Frame::build(const Scope* scope)
//[]----------------------------------------------------[]
//|  Build                                               |
//[]----------------------------------------------------[]
{
  if (scope != nullptr)
    for (auto& [name, v] : scope->_variables)
      add(new FrameRecord{name});
}

} // end namespace calc
