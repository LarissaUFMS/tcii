#include "String.h"

void
String::copy(const char const* s, size_t size)
{
  if ((_size = size) > 0)
  {
    if (isShort())
      _data = _buffer;
    else
    {
      _capacity = (_size / MAX_BUFFER + 1) * MAX_BUFFER;
      _data = new char[_capacity + 1];
    }
    strcpy(_data, s);
  }
}

void
String::move(String& other) noexcept
{
  _size = other._size;
  if (isShort())
  {
    _data = _buffer;
    strcpy(_data, other._data);
  }
  else
  {
    _capacity = other._capacity;
    _data = other._data;
  }
  other._size = 0;
}
