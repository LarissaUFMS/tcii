#ifndef __IntArray_h
#define __IntArray_h

#include <cassert>
#include <iostream>

class IntArray;

class IntArrayIterator
{
public:
  using value_type = int;
  using iterator = IntArrayIterator;

  bool operator ==(const iterator& other) const;

  bool operator !=(const iterator& other) const
  {
    return !operator ==(other);
  }

  iterator operator ++(int);
  iterator operator ++();

  int operator *() const;

private:
  const IntArray* _array;
  int _index;

  IntArrayIterator(const IntArray* array, int index):
    _array{array},
    _index{index}
  {
    // do nothing
  }

  friend IntArray;

}; // IntArrayIterator

class IntArray
{
public:
  using iterator = IntArrayIterator;

  IntArray();
  IntArray(int capacity);

  ~IntArray();

  void add(int value);
  bool remove(int value);
  void clear();

  bool contains() const;

  auto size() const
  {
    return _size;
  }

  bool empty() const
  {
    return _size == 0;
  }

  auto operator [](int index) const
  {
    assert(index >= 0 && index < _size);
    return _data[index];
  }

  auto& operator [](int index)
  {
    assert(index >= 0 && index < _size);
    return _data[index];
  }

  auto begin() const
  {
    return iterator{this, 0};
  }

  auto end() const
  {
    return iterator{this, _size};
  }

private:
  int _capacity;
  int _size;
  int* _data;

  void resize();
  int* find(int value) const;

}; // IntArray

inline bool
IntArrayIterator::operator ==(const iterator& other) const
{
  assert(_array == other._array);
  return _index == other._index;
}

inline IntArrayIterator
IntArrayIterator::operator ++(int)
{
  assert(_index < _array->size());

  auto temp = *this;

  ++_index;
  return temp;
}

inline IntArrayIterator
IntArrayIterator::operator ++()
{
  assert(_index < _array->size());
  ++_index;
  return *this;
}

inline int
IntArrayIterator::operator *() const
{
  return (*_array)[_index];
}

inline auto&
operator <<(std::ostream& os, const IntArray& a)
{
  os << '{';
  for (auto eit = a.end(), it = a.begin(); it != eit;)
    os << *it++ << ',';
  if (!a.empty())
    os << '\b';
  os << '}';
  return os;
}

#endif // __IntArray_h
