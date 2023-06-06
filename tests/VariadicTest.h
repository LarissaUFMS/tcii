#include <cmath>
#include <iostream>

namespace test
{ // namespace test

template <typename T>
inline constexpr auto
add(const T& t)
{
  return t;
}

template <typename T, typename... Ts>
inline constexpr auto
add(const T& t, Ts&&... ts)
{
  return t + add(std::forward<Ts>(ts)...);
}

template <typename T>
inline auto
compare(const T& a, const T& b)
{
  return a == b;
}

inline auto
compare(float a, float b)
{
  return std::fabs(a - b) <= 1e-6f;
}

template <typename T>
inline auto
pairComp(const T& a, const T& b)
{
  return compare(a, b);
}

template <typename T, typename... Ts>
inline auto
pairComp(const T& a, const T& b, Ts&&... ts)
{
  return compare(a, b) && pairComp(std::forward<Ts>(ts)...);
}

} // end namespace test

inline void
variadicTest()
{
  using namespace test;
  using namespace std;

  cout << "add(2): " << add(2) << '\n';
  cout << "add(2,3.14f,4,5): " << add(2, 3.14f, 4, 5) << '\n';

  auto pi = 3.14f;

  cout << "add(2,pi,4,5): " << add(2, pi, 4, 5) << '\n';
  cout << boolalpha << pairComp(pi, float(3), 3, 4) << '\n';
}
