#pragma once
#ifndef GEdge_HPP
#define GEdge_HPP
#include "GraphicsData.hpp"
#include "Point.hpp"
#include "Triangle.hpp"

using std::vector;
class Triangle;
class Point;

class Edge
{
    public:
        Edge();
        Edge(int p1, int p2);
        ~Edge();

        mutable int index = -1;
        vector<int> points;
        mutable vector<int> triangles;
        int midpoint;
        const void addTriangle(int t) const;
        int getOtherPoint(int p);
        bool operator==(const Edge &otherEdge) const;
};

typedef vector<Edge> Edge_List;
class EdgeMap
{
    public:
        EdgeMap();
        ~EdgeMap();
        Edge_List edges;
};

#endif // !GEdge_HPP