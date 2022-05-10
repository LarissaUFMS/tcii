#ifndef __String_h
#define __String_h

#include <cassert>
#include <string>

class String
{
public:
  ~String()
  {
    delete[]_data;
  }

  String() = default;
  String(const char* const);
  String(const String&);

  auto size() const
  {
    return _size;
  }

  auto empty() const
  {
    return _size == 0;
  }

  const char* c_str() const
  {
    return _data;
  }

  String& operator =(const String&);
  String& operator =(const char* const);

  String& operator +=(const String&);
  String& operator +=(const char* const);

  auto operator [](size_t i) const
  {
    assert(i <= _size);
    return _data[i];
  }

  String operator +(const String&) const;
  String operator +(const char* const) const;

  bool operator ==(const String&) const;
  bool operator ==(const char* const) const;

  auto operator !=(const String& s) const
  {
    return !operator ==(s);
  }

  auto operator !=(const char* const s) const
  {
    return !operator ==(s);
  }

private:
  size_t _size{};
  char* _data{};

}; // String

#endif // __String_h
