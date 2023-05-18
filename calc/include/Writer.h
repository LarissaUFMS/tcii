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
// OVERVIEW: Writer.h
// ========
// Class definition for print writer.
//
// Author: Paulo Pagliosa
// Last revision: 16/05/2023

#ifndef __Writer_h
#define __Writer_h

#include <iostream>
#include <fstream>

namespace calc
{ // begin namespace calc


/////////////////////////////////////////////////////////////////////
//
// Writer: print writer class
// ======
class Writer
{
public:
  Writer():
    _out{stdout}
  {
    // do nothing
  }

  Writer(const char* fileName):
    _out{fileName}
  {
    // do nothing
  }

  ~Writer()
  {
    _out.close();
  }

  void write(int c)
  {
    _out << (char)c;
  }

  void write(const char* format, ...);

  void beginBlock()
  {
    writeTabs();
    _out << "{\n";
    _level++;
  }

  void endBlock()
  {
    _level--;
    writeTabs();
    _out << "}\n";
  }

  void backspace()
  {
    _level--;
  }

  void tab()
  {
    _level++;
  }

  void beginLine()
  {
    writeTabs();
  }

  void endLine()
  {
    _out << '\n';
  }

private:
  void writeTabs();

  std::ofstream _out;
  int _level{};

}; // Writer

} // end namespace calc

#endif // __Writer_h
