#include <cmath>
#include <iostream>

namespace test
{ // namespace test

template <bool B, typename T = void>
struct enable_if
{
  // empty
};

template <typename T>
struct enable_if<true, T>
{
  using type = T;
};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

namespace std_14
{ // begin namespace std_14

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

} // end namespace std_14

template <typename... Ts>
inline constexpr auto
add(Ts&&... ts)
{
  return (... + ts);
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

template <typename T>
inline auto
pairComp(const T&)
{
  return false;
}

template <typename T, typename... Ts>
inline auto
pairComp(const T& a, const T& b, Ts&&... ts)
{
  return compare(a, b) && pairComp(std::forward<Ts>(ts)...);
}

template <typename... Ts>
struct tuple
{
  // empty
};

template <typename T, typename... Ts>
struct tuple<T, Ts...>: tuple<Ts...>
{
  T value;

  tuple(const T& t, Ts&&... ts):
    tuple<Ts...>{std::forward<Ts>(ts)...},
    value{t}
  {
    // do nothing
  }
};

template <size_t, typename> struct _tet;

template <typename T, typename... Ts>
struct _tet<0, tuple<T, Ts...>>
{
  using type = T;
};

template <size_t I, typename T, typename... Ts>
struct _tet<I, tuple<T, Ts...>>
{
  using type = typename _tet<I - 1, tuple<Ts...>>::type;
};

template <size_t I, typename... Ts>
enable_if_t<I == 0, typename _tet<0, tuple<Ts...>>::type&>
get(tuple<Ts...>& t)
{
  return t.value;
}

template <size_t I, typename T, typename... Ts>
enable_if_t<I != 0, typename _tet<I, tuple<T, Ts...>>::type&>
get(tuple<T, Ts...>& t)
{
  tuple<Ts...>& base{t};
  return get<I - 1>(base);
}

} // end namespace test

inline void
variadicTest()
{
  puts("\n**VARIADIC TEMPLATE TEST");

  using namespace test;
  using namespace std;

  cout << "add(2): " << add(2) << '\n';
  cout << "add(2,3.14f,4,5): " << add(2, 3.14f, 4, 5) << '\n';

  auto pi = 3.14f;

  cout << "add(2,pi,4,5): " << add(2, pi, 4, 5) << '\n';
  cout << boolalpha << pairComp(pi, float(3), 3, 4) << '\n';

  test::tuple<float, const char*, int> t{pi, "C++", 3};
  cout << test::get<2>(t);
}
