#include "geo/ShapeList.h"

namespace geo
{ // begin namespace geo

void
ShapeList::add(Shape* shape)
{
  auto node = new ShapeListNode{shape};

  if (_head == nullptr)
    _head = node;
  else
    _tail->_next = node;
  _tail = node;
  _size++;
}

void
ShapeList::clear()
{
  while (_head != nullptr)
  {
    auto temp = _head;

    _head = temp->_next;
    delete temp;
  }
  _size = 0;
}

void
ShapeList::iterate(ShapeFunc func) const
{
  for (auto node = _head; node != nullptr; node = node->_next)
    func(node->_shape);
}

} // end namespace geo
