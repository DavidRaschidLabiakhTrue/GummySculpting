#pragma once
#ifndef GOctree_HPP
#define GOctree_HPP

#include <algorithm>
#include <atomic>
#include <chrono>
#include <execution>
#include <iostream>
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "GraphicsData.hpp"
#include "MathDefinitions.hpp"

#include "Edge.hpp"
#include "Point.hpp"
#include "Triangle.hpp"
#include "Octant.hpp"
#include "Macro.hpp"
#include "glad/glad.h"
#include "glm/gtx/hash.hpp"


using namespace MathTypeDefinitions::CoordinateDefine;
using namespace GraphicsDataDefinition;
using namespace VertexDefinition;
using namespace glm;
using std::vector;

struct Collision
{
        int triangle;
        float distance;
        v3 pos;
};

struct edge_hash
{
        std::size_t operator()(const Edge &e) const
        {
            return std::hash<int>()(e.points[0]) ^ std::hash<int>()(e.points[1]);
        }
};

struct edge_equal
{
        bool operator()(const Edge &e1, const Edge &e2) const
        {
            return (e1.points[0] == e2.points[0] && e1.points[1] == e2.points[1]) ||
                   (e1.points[0] == e2.points[1] && e1.points[1] == e2.points[0]);
        }
};

struct point_hash
{
        std::size_t operator()(const Point &p) const
        {
            return std::hash<int>()(p.index);
            // V3 pos = VertexLookUp(p.index);
            // return (size_t)((int)(pos.x * 1000) ^ (int)(pos.y * 100) ^ (int)(pos.z * 10));
        }
};

struct point_equal
{
        bool operator()(const Point &p1, const Point &p2) const
        {
            return p1.index == p2.index;
        }
};

class Octree
{
    public:
        // EMPTY CONSTRUCTOR TO SILENCE C++.
        Octree();
        ~Octree();

        double tempLooseVal = 0;

        int limit = 1000;
        int depthLimit = 10;
        int depth = 0;
        double looseness = 0.2;
        int currentDepth = 0;
        vector<Octant> octants;
        unordered_set<int> leaves;
        vector<Point> points;
        vector<Edge> edges;
        unordered_set<Edge, edge_hash, edge_equal> edgeset;
        vector<Triangle> triangles;
        vector<v3> octreeVertices;
        Indices octreeIndices;


        Octree(vector<v3> &verts, Indices &indices);
        int findOctant(int t);
        int getNext(int o, int t);
        bool insert(int t);
        bool contains(Triangle t);
        bool remove(Triangle &t);
        vector<Point> collect(Collision &collision, double range);
        void resize(int t);
        Octant createParent(vec3 direction);
        Collision rayIntersection(v3 &origin, v3 direction);
        void octreeDebug();
        void subdivideOctant(int o);
        void generateMesh(bool trianglesOnly);
};

#endif