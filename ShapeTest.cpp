#include "Circle.h"
#include "LinkedList.h"
#include "Rectangle.h"

void
shapeInfo(const geo::Shape* shape)
{
  printf("Shape id: %d area: %.3f\n", shape->id(), shape->area());
}

void
shapeTest()
{
  using namespace geo;
  using namespace util;

  LinkedList<ShapePtr> shapes;

  printUsedMemory();
  shapes.add(Allocator::New<Circle>(Point2{2, 2}, 1.0f));
  shapes.add(Allocator::New<Circle>(Point2{3, 3}, 1.0f));
  shapes.add(Allocator::New<Rectangle>(Point2{4, 4}, 1.0f, 1.0f));
  //shapes.iterate(shapeInfo);
  for (auto s : shapes)
    shapeInfo(s);
  printUsedMemory();
}