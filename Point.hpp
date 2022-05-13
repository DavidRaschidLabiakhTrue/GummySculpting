#pragma once
#ifndef GPoint_HPP
#define GPoint_HPP
#include "GraphicsData.hpp"
#include "Edge.hpp"
#include "MathDefinitions.hpp"
#include "Triangle.hpp"

using std::vector;
using namespace MathTypeDefinitions::CoordinateDefine;
class Triangle;
class Edge;

class Point
{
    public:
        Point();
        Point(int index);
        ~Point();

        int index;
        vector<int> triangles;
        vector<int> edges;
        void addTriangle(int t);
        void addEdge(int e);
        bool operator==(const Point &otherPoint) const;
        bool equal(Point &otherPoint);
};

#endif // !GPoint_HPP