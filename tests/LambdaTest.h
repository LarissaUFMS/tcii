#ifndef __LambdaTest_h
#define __LambdaTest_h

#include <iostream>
#include <functional>
#include <string>

namespace test
{ // begin namespace test

template <typename... Args>
void
varprint(Args&&... args)
{
  (std::cout << ... << std::forward<Args>(args)) << '\n';
}

template <typename... Args>
using varfunc = std::function<void(Args&&...)>;

using strings = std::vector<std::string>;
using logfunc = std::function<void(const strings&)>;

inline void
logText(logfunc f)
{
  f({"UFMS", "FACOM", "Modern C++"});
}

template <typename... Args>
void log(std::ostream&, Args&&...);

inline void
testLog(std::ostream& os = std::cout)
{
  logText([&os](const auto& s)
    {
      for (size_t n = s.size(), i = 0; i < n; ++i)
        log(os, i + 1, ':', s[i]);
    });
}

template <typename... Args>
class Functor
{
public:
  Functor(const char* name):
    _name{name}
  {
    // do nothing
  }

  void operator ()(Args&&... args) const
  {
    varprint(_name, ':', std::forward<Args>(args)...);
  }

private:
  std::string _name;

}; // Functor

template <typename F, typename... Args>
inline void
call(F&& f, Args&&... args)
{
  f(std::forward<Args>(args)...);
}

} // end namespace test

inline void
lambdaTest()
{
  puts("\n**LAMBDA/FOLD EXPRESSION");

  using namespace test;

  const char* name = "test";

  Functor<int, int, int> f{name};
  auto fp = varfunc<int, int, int>{f};
  auto lf = [name](int i, int j, int k)
  {
    varprint(name, ':', i, j, k);
  };

  f(1, 2, 3);
  call(fp, 1, 2, 3);
  fp = lf;
  call(fp, 1, 2, 3);
}

#endif // __LambdaTest_h
