#ifndef __FuncTemplateTest_h
#define __FuncTemplateTest_h

#include <string>

namespace test
{ // begin namesapce test

// A base template
template <typename T>
inline constexpr auto
max(const T& a, const T& b)
{
  return a > b ? a : b;
}

// Specialization for string
template <>
inline auto
max<std::string>(const std::string& a, const std::string& b)
{
  return a.size() > b.size() ? a : b;
}

// Overload for int
inline constexpr auto
max(int a, int b)
{
  return a > b ? a : b;
}

// Another base template
template <int N>
inline auto
fat()
{
  return N * fat<N - 1>();
}

// Specialization for 1
template <>
inline auto
fat<1>()
{
  return 1;
}

// A constexpr function works
inline constexpr auto
cfat(int n) -> decltype(n)
{
  return n <= 1 ? 1 : n * cfat(n - 1);
}

} // end namesapce test

inline void
funcTemplateTest()
{
  puts("\n**FUNCTION TEMPLATES/CONSTEXPR FUNCTION");

  using namespace test;

  int i = 2;
  int j = 3;

  printf("max(i,j): %d\n", max<int>(i, j));
  printf("max(2,3): %d\n", max<int>(2, 3));
  printf("fat(5): %d\n", fat<5>());
  printf("fat(j): %d\n", cfat(j)); // runtime evaluation!
  printf("fat(3): %d\n", cfat(3));
}

#endif // __FuncTemplate_h
