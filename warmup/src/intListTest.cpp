#include <stdio.h>
#include "IntList.h"

void
printi(int i)
{
  printf("%d\n", i);
}

int
main()
{
  IntList list;

  for (int i = 1; i < 10; i++)
    list.add(i);
  list.iterate(printi);

  IntNode* node = list.find(5);

  if (node != nullptr)
    printf("5 found\n");
  if (list.remove(5))
  {
    printf("5 removed\n");
    list.iterate(printi);
  }
  puts("Press any key to exit...");
  getchar();
  return 0;
}
