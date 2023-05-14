#ifndef __ShapeTest_h
#define __ShapeTest_h

#include "geo/Circle.h"
#include "geo/Rectangle.h"
#include "geo/ShapeList.h"
#include "util/LinkedList.h"

//#define _USE_SHAPE_LIST

namespace test
{ // begin namespace test

inline void
shapeInfo(const geo::Shape* shape)
{
  printf("Shape id: %d area: %.3g\n", shape->id(), shape->area());
}

} // end namespace test

inline void
shapeTest()
{
  puts("\n**BASIC INHERITANCE/DYNAMIC BINDING");

  using namespace geo;

#ifdef _USE_SHAPE_LIST
  ShapeList shapes;

  shapes.add(new Circle{{2, 2}, 1.0f});
  shapes.add(new Circle{{3, 3}, 1.0f});
  shapes.add(new Rectangle{{4, 4}, 1.0f, 1.0f});
  shapes.iterate(shapeInfo);
#else
  using namespace util;
  using namespace test;

  LinkedList<ShapePtr> shapes;

  printUsedMemory();
  shapes.add(Allocator::New<Circle>(Point2{2, 2}, 1.0f));
  shapes.add(Allocator::New<Circle>(Point2{3, 3}, 1.0f));
  shapes.add(Allocator::New<Rectangle>(Point2{4, 4}, 1.0f, 1.0f));
  shapes.iterate(shapeInfo);
  for (auto s : shapes)
    shapeInfo(s);
  printUsedMemory();
#endif // _USE_SHAPE_LIST
}

#endif // __ShapeTest_h
