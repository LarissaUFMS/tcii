#include "util/IntLinkedList.h"

namespace tcii
{ // begin namespace tcii

void
IntLinkedList::clear()
{
  while (_head != nullptr)
  {
    auto temp = _head;

    _head = temp->_next;
    delete temp;
  }
  _tail = nullptr;
  _count = 0;
}

void
IntLinkedList::add(int value)
{
  auto node = new IntNode{value};

  if (_head == nullptr)
    _head = node;
  else
    _tail->_next = node;
  _tail = node;
  ++_count;
}

IntLinkedListIterator
IntLinkedList::find(int value) const
{
  for (IntNode* node = _head; node != nullptr; node = node->_next)
    if (node->_value == value)
      return {this, node};
  return end();
}

bool
IntLinkedList::remove(int value)
{
  auto pp = &_head;

  for (IntNode* prev = nullptr; *pp != nullptr; prev = *pp, pp = &prev->_next)
    if ((*pp)->_value == value)
    {
      auto temp = *pp;

      if (temp == _tail)
        _tail = prev;
      *pp = temp->_next;
      delete temp;
      --_count;
      return true;
    }
  return false;
}

} // end namespace tcii
