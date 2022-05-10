#ifndef __Util_h
#define __Util_h

#include <functional>
#include <map>
#include <utility>
#include <cstdio>

namespace util
{ // begin namespace util

class Allocator
{
public:
  struct TypeInfo
  {
    size_t size;
    const char* name;

  }; // TypeInfo

  using DebugFunc = std::function<void(const void*, const TypeInfo&)>;

  static auto usedMemory()
  {
    return _usedMemory;
  }

  static void debug(DebugFunc func)
  {
    for (const auto& e : _memoryMap)
      func(e.first, e.second);
  }

  template <typename T, typename... Args>
  static auto New(Args&&... args)
  {
    auto ptr = new T(std::forward<Args>(args)...);
    auto typeInfo = TypeInfo{sizeof(T), typeid(T).name()};

    _usedMemory += typeInfo.size;
    _memoryMap[ptr] = typeInfo;
    return ptr;
  }

  template <typename T>
  static bool Delete(T* ptr)
  {
    if (auto e = _memoryMap.find(ptr); e != _memoryMap.end())
    {
      _usedMemory -= e->second.size;
      _memoryMap.erase(e);
      delete ptr;
      return true;
    }
    return false;
  }

private:
  inline static size_t _usedMemory;
  inline static std::map<const void*, TypeInfo> _memoryMap;

}; // Allocator

} // end namespace util

inline void
printUsedMemory()
{
  printf("Used Memory: %lld bytes\n", util::Allocator::usedMemory());
}

inline void
printMemoryMap()
{
  puts("       Ptr       | Size (B) | Type Name");
  util::Allocator::debug([](auto ptr, const auto& typeInfo)
    {
      printf("%p | %08lld | %s\n", ptr, typeInfo.size, typeInfo.name);
    });
}

#endif // __Util_h
