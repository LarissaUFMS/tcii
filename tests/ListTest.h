#ifndef __ListTest_h
#define __ListTest_h

#include "util/ObjectPtrList.h"

namespace test
{ // begin namespace test

inline void
printInt(int i)
{
  printf("%d\n", i);
}

struct S: public util::SharedObject
{
  int id;

  S(int id):
    id{id}
  {
    // do nothing
  }

  ~S()
  {
    printf("S::~S(): %d\n", id);
  }

}; // S

} // end namespace test

inline void
objectPtrListTest()
{
  using namespace test;

  util::ObjectPtrList<S> list;

  for (int i = 0; i < 10; ++i)
    list.add(new S{i});
  for (auto s : list)
    test::printInt(s->id);
  // Test question:
  // list is destroyed but S dtor is never invoked. Why?
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
    test::printInt(*lit);
  for (auto i : list)
    test::printInt(i);
  util::printUsedMemory();
  util::printMemoryMap();
  list.clear();
  util::printUsedMemory();
}

#endif // __ListTest_h
