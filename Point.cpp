#include "Point.hpp"

Point::Point()
{
}

Point::Point(int index)
{
    this->index = index;
}

Point::~Point()
{
}

void Point::addTriangle(int t)
{
    this->triangles.emplace_back(t);
}

void Point::addEdge(int e)
{
    this->edges.emplace_back(e);
}

// bool Point::operator==(const Point &otherPoint) const
// {
//     return index == otherPoint.index;
// }

bool Point::equal(Point &otherPoint)
{
    return otherPoint.index == index;
}