#ifndef __FunctionTemplate_h
#define __FunctionTemplate_h

#include "String.h"

namespace ft
{ // begin namesapce ft

template <typename T>
inline constexpr auto
max(const T& a, const T& b)
{
  return a > b ? a : b;
}

inline constexpr auto
max(int a, int b)
{
  return a > b ? a : b;
}

template <>
inline auto
max<String>(const String& a, const String& b)
{
  return a.size() > b.size() ? a : b;
}

template <int N>
inline auto
fat()
{
  return N * fat<N - 1>();
}

template <>
inline auto
fat<1>()
{
  return 1;
}

inline constexpr auto
cfat(int n) -> decltype(n)
{
  return n <= 1 ? 1 : n * cfat(n - 1);
}

} // end namesapce ft

#endif // __FunctionTemplate_h
