#include "Triangle.hpp"

Triangle::Triangle()
{
}

Triangle::Triangle(int p1, int p2, int p3, int index)
{
    this->index = index;
    this->points.emplace_back(p1);
    this->points.emplace_back(p2);
    this->points.emplace_back(p3);
    // this->centroid = (VertexLookUp(p1) + VertexLookUp(p2) + VertexLookUp(p3)) / 3.0f;
}

Triangle::~Triangle()
{
}

void Triangle::addEdge(int e)
{
    this->edges.emplace_back(e);
}

void Triangle::addPoint(int p)
{
    this->points.emplace_back(p);
}