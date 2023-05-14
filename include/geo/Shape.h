#ifndef __Shape_h
#define __Shape_h

#include "util/Allocator.h"
#include "util/SharedObject.h"

namespace geo
{ // begin namespace geo

class Shape: public util::SharedObject
{
public:
  virtual ~Shape() = default;

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

using ShapePtr = util::ObjectPtr<Shape>;

} // end namespace geo

namespace util
{ // begin namespace util

inline void
destroy(geo::Shape* shape)
{
  Allocator::Delete(shape);
}

} // end namespace util

#endif // __Shape_h
