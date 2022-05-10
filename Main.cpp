#include "FunctionTemplate.h"
#include "LinkedList.h"

void typeTest();
void vectorTest();
void matrixTest();
void shapeTest();

inline void
ftTest()
{
  int i = 2;
  int j = 3;

  printf("max(i,j): %d\n", ft::max<int>(i, j));
  printf("max(2,3): %d\n", ft::max<int>(2, 3));
  printf("fat(5): %d\n", ft::fat<5>());
  printf("fat(j): %d\n", ft::cfat(j));
  printf("fat(3): %d\n", ft::cfat(3));
}

void
printInt(int i)
{
  printf("%d\n", i);
}

inline void
listTest()
{
  util::LinkedList<int> list;

  for (int i = 0; i < 10; ++i)
    list.add(i);
  list.iterate(printInt);
  for (auto end = list.end(), lit = list.begin(); lit != end; ++lit)
    printInt(*lit);
  for (auto i : list)
    printInt(i);
  printUsedMemory();
  printMemoryMap();
  list.clear();
  printUsedMemory();
}

int
main()
{
  //typeTest();
  vectorTest();
  //matrixTest();
  /*
  String s1;
  String s2 = "c";
  String s3 = s2;

  s1 = s3;
  printf("s1:%s (size: %lld)\n", s1.c_str(), s1.size());
  */
  /*
  shapeTest();
  printUsedMemory();
  printMemoryMap();
  */
  //ftTest();
  //listTest();
  puts("Press any key to exit...");
  (void)getchar();
  return 0;
}