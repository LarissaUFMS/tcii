#include "geo/Circle.h"

namespace geo
{ // begin namespace geo

Circle::Circle(const Point2& center, float radius):
	center{center}
{
	setRadius(radius);
}

void
Circle::setRadius(float radius)
{
	_radius = radius > 0 ? radius : 0;
}

float
Circle::area() const
{
	constexpr auto pi = float(3.14159265358979323846);
	return pi * _radius * _radius;
}

} // end namespace geo
