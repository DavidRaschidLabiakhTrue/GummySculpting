#ifndef Octant_HPP
#define Octant_HPP

#include "MeshStats.hpp"

namespace OctantDefinition
{
	using namespace MeshStatsDefinition;
	typedef int OctantIndex;
	typedef int ChildArray;
	typedef int OctantParent;

	typedef vector<int> TriangleIDList;

	#define NoOctantParentSet -1

	/*
	*	To be used in Octree - Data Container for 3d data
	*/
	class Octant
	{
		public:
			Octant();
			Octant(v3 center, double halfsize, int limit, int index);
			~Octant();

			OctantIndex octantIndex; // store octant index on the octant itself.
			TriangleIDList triangleID; // references to positions within the triangle array
			OctantParent parent = NoOctantParentSet; // integer id to parent within octant list
			ChildArray children[8] = { -1, -1, -1, -1, -1, -1, -1, -1 }; // integer IDs to octant children within the OctantList

			float octantHalfSize;
			v3 octantCenter; // center position of octant
			int octantDepth; // octant depth level
			int octantState = 2; // this needs to be enumerated
			int octantLimit;
	};



}

#endif // !Octant_HPP



/*
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
#include "Octree.hpp"
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
using namespace MeshStatsDefinition;
using std::vector;

class Octant : public MeshStats
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
*/