#include "String.h"

String::String(const char* const s)
{
  if ((_size = strlen(s)) > 0)
  {
    _data = new char[_size + 1];
    strcpy(_data, s);
  }
}

String::String(const String& other)
{
  if ((_size = other._size) > 0)
  {
    _data = new char[_size + 1];
    strcpy(_data, other._data);
  }
}

String&
String::operator =(const String& other)
{
  if (&other != this)
  {
    if (_size != other._size)
    {
      delete[]_data;
      _data = (_size = other._size) > 0 ? new char[_size + 1] : nullptr;
    }
    if (_data)
      strcpy(_data, other._data);
  }
  return *this;
}
