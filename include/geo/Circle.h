#ifndef __Circle_h
#define __Circle_h

#include "geo/Point2.h"
#include "geo/Shape.h"

namespace geo
{ // begin namespace geo

class Circle: public Shape
{
public:
  Point2 center;

  Circle(const Point2& center, float radius);

  auto radius() const
  {
    return _radius;
  }

  void setRadius(float radius);

  float area() const override;

private:
  float _radius;

}; // Circle

inline auto
area(const Circle& circle)
{
  return circle.area();
}

} // end namespace geo

#endif // __Circle_h
