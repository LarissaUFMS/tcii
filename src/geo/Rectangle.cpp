#include "geo/Rectangle.h"

namespace geo
{ // begin namespace geo

Rectangle::Rectangle(const Point2& center, float width, float height):
	center{center}
{
	setWidth(width);
	setHeight(height);
}

void
Rectangle::setWidth(float width)
{
	_width = width > 0 ? width : 0;
}

void
Rectangle::setHeight(float height)
{
	_height = height > 0 ? height : 0;
}

float
Rectangle::area() const
{
	return _width * _height;
}

} // end namespace geo
