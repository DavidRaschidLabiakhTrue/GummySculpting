/*
#include "GEdge.hpp"

GEdge::GEdge() {

}

GEdge::GEdge(int p1, int p2)
{
    this->points.emplace_back(p1);
    this->points.emplace_back(p2);
}

GEdge::~GEdge()
{
}

int GEdge::getOtherPoint(int p)
{
    return p == points[0] ? points[1] : points[0];
}

bool GEdge::operator==(const GEdge& otherEdge) const
{
    return (otherEdge.points[0] == points[0] && otherEdge.points[1] == points[1]) ||
        (otherEdge.points[0] == points[1] && otherEdge.points[1] == points[0]);
}

const void GEdge::addTriangle(int t) const
{
    this->triangles.emplace_back(t);
}
*/