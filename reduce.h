#include "IntArray.h"

class IntLinkedList;

int
sum(int* a, int n)
{
  auto s = 0;

  for (int i = 0; i < n; ++i)
    s += a[i];
  return s;
}

int
sum(const IntArray& a)
{
  auto s = 0;

  /*
  for (int i = 0; i < a.size(); ++i)
    s += a[i];
  */
  for (auto eit = a.end(), it = a.begin(); it != eit;)
    s += *it++;
  return s;
}

int
sum(const IntCollection& c)
{
  auto s = 0;

  for (auto eit = c.end(), it = c.begin(); it != eit;)
    s += *it++;
  return s;
}
