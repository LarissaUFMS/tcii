#ifndef __ShapeList_h
#define __ShapeList_h

#include "geo/Shape.h"
#include <functional>

namespace geo
{ // begin namespace geo

//
// Forward definition
//
class ShapeList;

class ShapeListNode
{
public:
  ~ShapeListNode()
  {
    delete _shape;
  }

private:
  ShapeListNode* _next{};
  Shape* _shape;

  ShapeListNode(Shape* shape):
    _shape{shape}
  {
    // do nothing
  }

  friend ShapeList;

}; // ShapeListNode

class ShapeList
{
public:
  using ShapeFunc = std::function<void(const Shape*)>;

  ~ShapeList()
  {
    clear();
  }

  ShapeList() = default;

  auto size() const
  {
    return _size;
  }

  void add(Shape*);
  void clear();

  void iterate(ShapeFunc func) const;

private:
  ShapeListNode* _head{};
  ShapeListNode* _tail{};
  size_t _size{};

}; // ShapeList

} // end namespace geo

#endif // __ShapeList_h
