#include "Edge.hpp"

Edge::Edge() {

}

Edge::Edge(int p1, int p2)
{
    this->points.emplace_back(p1);
    this->points.emplace_back(p2);
}

Edge::~Edge()
{
}

int Edge::getOtherPoint(int p)
{
    return p == points[0] ? points[1] : points[0];
}

bool Edge::operator==(const Edge &otherEdge) const
{
    return (otherEdge.points[0] == points[0] && otherEdge.points[1] == points[1]) ||
           (otherEdge.points[0] == points[1] && otherEdge.points[1] == points[0]);
}

const void Edge::addTriangle(int t) const
{
    this->triangles.emplace_back(t);
}