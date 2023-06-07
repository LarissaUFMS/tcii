#ifndef __IntArray_h
#define __IntArray_h

#include <stdio.h>

#define DFL_ARRAY_SIZE 10

extern void indexOutOfBoundsError(int, int);

typedef void (*IterFunc)(int);


class Array
{
private:
  int capacity;
  int delta;
  int count;
  int* data;

  void resize();

public:
  // Constructors
  Array(int = DFL_ARRAY_SIZE, int = DFL_ARRAY_SIZE);
  Array(const Array&);

  // Destructor
  ~Array();

  void add(int);
  void add(const Array&);
  bool remove(int);
  void clear();

  Array operator +(const Array&) const;
  int operator [](int) const;

  Array& operator +=(const Array&);
  int& operator [](int);

  bool isEmpty() const;
  bool contains(int) const;
  int size() const;
  void iterate(IterFunc) const;

}; // Array

inline
Array::Array(int capacity, int delta)
{
  this->capacity = capacity <= 0 ? DFL_ARRAY_SIZE : capacity;
  this->delta = delta < 0 ? DFL_ARRAY_SIZE : delta;
  data = new int[this->capacity];
  count = 0;
  printf("Ctor OK\n");
}

inline
Array::~Array()
{
  delete []data;
  printf("Dtor OK\n");
}

inline void
Array::add(int value)
{
  if (count + 1 == capacity)
    resize();
  data[count++] = value;
}

inline void
Array::clear()
{
  count = 0;
}

inline Array
Array::operator +(const Array& a) const
{
  return Array(*this).operator +=(a);
}

inline int
Array::operator [](int i) const
{
  if (i < 0 || i >= count)
    indexOutOfBoundsError(i, count);
  return data[i];
}

inline Array&
Array::operator +=(const Array& a)
{
  add(a);
  return *this;
}

inline int&
Array::operator [](int i)
{
  if (i < 0 || i >= count)
    indexOutOfBoundsError(i, count);
  return data[i];
}

inline bool
Array::isEmpty() const
{
  return count == 0;
}

inline int
Array::size() const
{
  return count;
}

#endif // __IntArray_h
