#ifndef __ListTest_h
#define __ListTest_h

#include "util/LinkedList.h"

inline void
printInt(int i)
{
  printf("%d\n", i);
}

inline void
listTest()
{
  util::LinkedList<int> list;
  int sum{};

  for (int i = 0; i < 10; ++i)
    list.add(i);
  list.iterate([&sum](auto i)
    {
      sum += i;
    }
  );
  printf("Sum: %d\n", sum);
  for (auto end = list.end(), lit = list.begin(); lit != end; ++lit)
    printInt(*lit);
  for (auto i : list)
    printInt(i);
  util::printUsedMemory();
  util::printMemoryMap();
  list.clear();
  util::printUsedMemory();
}

#endif // __ListTest_h
