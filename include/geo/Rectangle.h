#ifndef __Rectangle_h
#define __Rectangle_h

#include "geo/Point2.h"
#include "geo/Shape.h"

namespace geo
{ // begin namespace geo

class Rectangle: public Shape
{
public:
  Point2 center;

  Rectangle(const Point2& center, float width, float height);

  auto width() const
  {
    return _width;
  }

  void setWidth(float width);

  auto height() const
  {
    return _height;
  }

  void setHeight(float height);

  float area() const override;

private:
  float _width;
  float _height;

}; // Rectangle

inline auto
area(const Rectangle& rectangle)
{
  return rectangle.area();
}

} // end namespace geo

#endif // __Rectangle_h
