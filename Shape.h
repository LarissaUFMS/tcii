#ifndef __Shape_h
#define __Shape_h

#include "Util.h"

namespace geo
{ // begin namespace geo

class Shape
{
public:
  auto id() const
  {
    return _id;
  }

  virtual float area() const = 0;

protected:
  Shape() :
    _id(nextShapeId())
  {
    // do nothing
  }

private:
  int _id;

  static int nextShapeId()
  {
    static int nextId;
    return ++nextId;
  }

}; // Shape

} // end namespace geo

#endif // __Shape_h
