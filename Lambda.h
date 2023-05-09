#ifndef __Lambda_h
#define __Lambda_h

#include <iostream>
#include <functional>
#include <string>

template <typename... Args>
void
varprint(Args&&... args)
{
  (std::cout << ... << std::forward<Args>(args)) << '\n';
}

template <typename... Args>
using varfunc = std::function<void(Args&&...)>;

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

#endif // __Lambda_h
