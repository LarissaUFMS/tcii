#ifndef __String_h
#define __String_h

#include <cassert>
#include <string>

class String
{
public:
  ~String()
  {
    if (!isShort())
      delete[] _data;
  }

  String():
    _size{},
    _data{_buffer}
  {
    _data[0] = 0;
  }

  String(const char* const s)
  {
    copy(s, strlen(s));
  }

  String(const String& other)
  {
    copy(other._data, other._size);
  }

  String(String&& other) noexcept
  {
    move(other);
  }

  auto size() const
  {
    return _size;
  }

  auto capacity() const
  {
    return isShort() ? MAX_BUFFER - 1 : _capacity;
  }

  auto empty() const
  {
    return _size == 0;
  }

  const char* c_str() const
  {
    return _data;
  }

  String& operator =(const char* const s)
  {
    this->~String();
    copy(s, strlen(s));
    return *this;
  }

  String& operator =(const String& other)
  {
    if (this != &other)
    {
      this->~String();
      copy(other._data, other._size);
    }
    return *this;
  }

  String& operator =(String&& other) noexcept
  {
    if (this != &other)
    {
      this->~String();
      move(other);
    }
    return *this;
  }

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
  static constexpr size_t MAX_BUFFER = 16;

  size_t _size;
  char* _data;
  union
  {
    size_t _capacity;
    char _buffer[MAX_BUFFER];
  };

  bool isShort() const
  {
    return _size < MAX_BUFFER;
  }

  void copy(const char* const, size_t);
  void move(String&) noexcept;

}; // String

#endif // __String_h
