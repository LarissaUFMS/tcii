#ifndef __LinkedList_h
#define __LinkedList_h

#include "Util.h"
#include <cassert>
#include <functional>

namespace util
{ // begin namespace util

//
// Forward definitions
//
template <typename T> class LinkedList;
template <typename T> class LinkedListIterator;

template <typename T>
class LinkedListNode
{
private:
  LinkedListNode<T>* _next{};
  T _value;

  LinkedListNode(const T& value) :
    _value{ value }
  {
    // do nothing
  }

  friend LinkedList<T>;
  friend LinkedListIterator<T>;
  friend Allocator;

}; // LinkedListNode

template <typename T>
class LinkedListIterator
{
public:
  using Iterator = LinkedListIterator<T>;
  using List = LinkedList<T>;

  LinkedListIterator(const List* list, const LinkedListNode<T>* node):
    _list{list},
    _node{node}
  {
    // do nothing
  }

  auto operator ==(const Iterator& other) const
  {
    return _list == other._list && _node == other._node;
  }

  auto operator !=(const Iterator& other) const
  {
    return !operator ==(other);
  }

  auto& operator ++()
  {
    assert(_node != nullptr);
    _node = _node->_next;
    return *this;
  }

  auto operator ++(int) // post-increment
  {
    auto temp = *this;

    operator ++();
    return temp;
  }

  const auto& operator *() const
  {
    assert(_node != nullptr);
    return _node->_value;
  }

  const auto& operator ->() const
  {
    return operator *();
  }

private:
  const List* _list;
  const LinkedListNode<T>* _node;

}; // LinkedListIterator

template <typename T>
using IterFunc = std::function<void(const T&)>;

template <typename T>
class LinkedList
{
public:
  ~LinkedList()
  {
    clear();
  }

  LinkedList() = default;

  auto size() const
  {
    return _size;
  }

  void add(const T&);
  void clear();

  void iterate(IterFunc<T> func) const;

  auto begin() const
  {
    return LinkedListIterator<T>{this, _head};
  }

  auto end() const
  {
    return LinkedListIterator<T>{this, nullptr};
  }

private:
  LinkedListNode<T>* _head{};
  LinkedListNode<T>* _tail{};
  size_t _size{};

}; // LinkedList

template <typename T>
void
LinkedList<T>::add(const T& value)
{
  auto node = Allocator::New<LinkedListNode<T>>(value);

  if (_head == nullptr)
    _head = node;
  else
    _tail->_next = node;
  _tail = node;
  _size++;
}

template <typename T>
void
LinkedList<T>::clear()
{
  while (_head != nullptr)
  {
    auto temp = _head;

    _head = temp->_next;
    Allocator::Delete(temp);
  }
  _size = 0;
}

template <typename T>
void
LinkedList<T>::iterate(IterFunc<T> func) const
{
  for (auto node = _head; node != nullptr; node = node->_next)
    func(node->_value);
}

} // end namespace util

#endif // __LinkedList_h
