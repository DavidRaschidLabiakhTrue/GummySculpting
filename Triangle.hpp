#pragma once
#ifndef GTriangle_HPP
#define GTriangle_HPP
#include <unordered_set>

#include "GraphicsData.hpp"
#include "MathDefinitions.hpp"
#include "Edge.hpp"
#include "Point.hpp"

using std::vector;
using namespace MathTypeDefinitions::CoordinateDefine;
using namespace GraphicsDataDefinition;

class Point;
class Edge;

class Triangle
{
    public:
        Triangle();
        Triangle(int p1, int p2, int p3, int index);
        ~Triangle();

        int octant;
        vector<int> points;
        vector<int> edges;
        int index;
        v3 centroid;

        void addEdge(int e);
        void addPoint(int p);
};

#endif // !GTriangle_HPP