#include <stdlib.h>
#include "IntArray.h"

void
indexOutOfBoundsError(int i, int n)
{
  printf("Index %d must be between 0 and %d\n.", i, n - 1);
  exit(EXIT_FAILURE);
}

void
Array::resize()
{
  int* newData = new int[capacity += delta];

  for (int i = 0; i < count; i++)
    newData[i] = data[i];
  delete []data;
  data = newData;
}

Array::Array(const Array& a)
{
  capacity = a.capacity;
  delta = a.delta;
  count = a.count;
  data = new int[capacity];
  for (int i = 0; i < count; i++)
    data[i] = a.data[i];
  printf("Copy ctor OK\n");
}

void
Array::add(const Array& a)
{
  for (int i = 0; i < a.count; i++)
    add(a.data[i]);
}

bool
Array::remove(int value)
{
  for (int i = 0; i < count; i++)
    if (data[i] == value)
    {
      --count;
      while (i++ < count)
        data[i - 1] = data[i];
      return true;
    }
  return false;
}

bool
Array::contains(int value) const
{
  for (int i = 0; i < count; i++)
    if (data[i] == value)
      return true;
  return false;
}

void
Array::iterate(IterFunc func) const
{
  for (int i = 0; i < count; i++)
    func(data[i]);
}
