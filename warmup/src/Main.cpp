#include <stdio.h>
#include <string>
#include "IntArray.h"

using namespace std;

void
print(int i)
{
  printf("%d\n", i);
}

string
getFirstName()
{
  return "LPOO";
}

string
getLastName()
{
  return "FACOM";
}

string
getFullName()
{
  return getFirstName() + '-' + getLastName();
}

Array
range(int a, int b)
{
  Array r(b - a + 1);

  for (; a <= b; a++)
    r.add(a);
  return r;
}

Array&
range(Array& r, int a, int b)
{
  r.clear();
  for (; a <= b; a++)
    r.add(a);
  return r;
}

int
main()
{
  puts(getFullName().c_str());

  Array a = range(1, 6) + range(27, 33);

  /*
  Array r;

  a.add(range(r, 1, 6));
  a.add(range(r, 27, 33));
  a.iterate(print);
  */
  /*
  if (a.isEmpty())
    puts("Array is empty.");
  for (int i = 0; i < 20; i++)
    a.add(i);
  if (a.contains(5))
    puts("5 is found.");
  if (a.remove(19))
    puts("19 has been removed.");
  if (a.remove(10))
    puts("10 has been removed.");
  printf("Number of elements: %d\n", a.size());
  a[5] = 100;
  printf("Element 5: %d\n", a[5]);
  a.iterate(print);
  */
  puts("Press any key to exit...");
  getchar();
  return 0;
}
