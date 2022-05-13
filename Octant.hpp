#pragma once
#ifndef GOctant_HPP
#define GOctant_HPP
#include <algorithm>
#include <atomic>
#include <chrono>
#include <execution>
#include <iostream>
#include <random>
#include <vector>
#include <cmath>

#include "GraphicsData.hpp"
#include "MathDefinitions.hpp"
#include "Point.hpp"
#include "Triangle.hpp"
#include "Camera.hpp"
// #include "Debug.hpp"
#include "Shader.hpp"
#include "Macro.hpp"
#include "glad/glad.h"

// using namespace GDebug;
using namespace MathTypeDefinitions::CoordinateDefine;
using namespace GraphicsDataDefinition;
using namespace VertexDefinition;
using std::vector;

class Octant
{
    public:
        vector<int> tris;
        int index;
        float halfsize;
        v3 center;
        int children[8] = {0};
        int state = 2;
        int parent = -1;
        int depth = 0;

        Octant();
        Octant(v3 center, double halfsize, int limit, int index);
        ~Octant();

        int limit;
        bool contains(int t);
        bool inBounds(vector<int> &points);
        bool insert(int t);
        vector<Octant> subdivide(int octantsIndex, double looseness);
        vector<v3> generateMesh();
};

inline extern int morton(v3 point, v3 center);

#endif