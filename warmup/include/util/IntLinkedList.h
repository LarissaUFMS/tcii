#ifndef __IntLinkedList_h
#define __IntLinkedList_h

#include <cassert>

namespace tcii
{ // begin namespace tcii

class IntLinkedList;
class IntLinkedListIterator;

class IntNode
{
  int _value{};
  IntNode* _next{};

  IntNode() = default;

  IntNode(int value):
    _value{value}
  {
    // do nothing
  }

  friend IntLinkedList;
  friend IntLinkedListIterator;

}; // IntNode

class IntLinkedListIterator
{
public:
  using iterator = IntLinkedListIterator;

  bool operator ==(const iterator& other) const
  {
    assert(_list == other._list);
    assert(_node != nullptr);
    return _node->_value == other._node->_value;
  }

  bool operator !=(const iterator& other) const
  {
    return !operator ==(other);
  }

  iterator operator ++(int)
  {
    assert(_node != nullptr);

    auto temp = *this;

    _node = _node->_next;
    return temp;
  }

  iterator& operator ++()
  {
    assert(_node != nullptr);
    _node = _node->_next;
    return *this;;
  }
  
  auto operator *() const
  {
    assert(_node != nullptr);
    return _node->_value;
  }

private:
  const IntLinkedList* _list;
  IntNode* _node;

  IntLinkedListIterator(const IntLinkedList* list, IntNode* node):
    _list{list},
    _node{node}
  {
    // do nothing
  }

  friend IntLinkedList;

}; // IntLinkedListIterator

class IntLinkedList
{
public:
  using iterator = IntLinkedListIterator;

  ~IntLinkedList()
  {
    clear();
  }

  void clear();
  void add(int value);
  bool remove(int value);

  iterator find(int value) const;

  bool contains(int value) const
  {
    return find(value)._node != nullptr;
  }

  auto size() const
  {
    return _count;
  }

  bool empty() const
  {
    return _count == 0;
  }

  auto begin() const
  {
    return iterator{this, _head};
  }

  auto end() const
  {
    return iterator{this, nullptr};
  }

private:
  IntNode* _head{};
  IntNode* _tail{};
  int _count{};

}; // IntLinkedList

} // end namespace tcii

#endif // __IntLinkedList_h
