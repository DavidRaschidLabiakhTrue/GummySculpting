#pragma once
#ifndef Octree_HPP
#define Octree_HPP

#include "MeshStats.hpp"
#include "Octant.hpp"
#include "OctreeCollision.hpp"
#include "OctreeStats.hpp"
#include "VertexIDHashing.hpp"

#include <chrono>
#include <queue>
#include <unordered_set>
// #include <bits/stdc++.h>

namespace OctreeDefinition
{
    using namespace MeshStatsDefinition;   // this is all that's needed as it auto includes everything it needs and uses
    using namespace OctreeStatsDefinition; // decoupling
    using namespace OctantDefinition;
    using namespace OctreeCollisionDefinition; // I am using collision
    using namespace VertexIDHashingDefinition;
    using std::unordered_set;

    typedef unordered_set<OctantIndex> OctantLeavesList;

#define MortonCodeConvert_Safe(MortonCodeVertexPosition, MortonCodeCenterPosition) (((((MortonCodeVertexPosition) == 0.0f) && std::signbit((MortonCodeVertexPosition))) ? 0.0f : (MortonCodeVertexPosition)) >= (MortonCodeCenterPosition))

// Uncomment this line to apply no except to every octree function to boost performance
#define USING_NOEXCEPT_OCTREE

#ifndef USING_NOEXCEPT_OCTREE
#define ONOEXCEPT
#else
#define ONOEXCEPT noexcept
#endif

    class Octree : public OctreeStats
    {
        public:
            // Octree.cpp
            void buildOctree() ONOEXCEPT;
            void testOctree() ONOEXCEPT;
            void octreePrintStats() ONOEXCEPT;
            void resizeOctree(TriangleID tri) ONOEXCEPT;
            void clearOctree() ONOEXCEPT;
            void rebuildOctree() ONOEXCEPT;

            // OctreeOctant.cpp
            void subdivideOctant(OctantIndex octantID) ONOEXCEPT;
            void createChildOctant(OctantPosition octantPosition, OctantIndex parentIndex) ONOEXCEPT;
            OctantIndex findOctantForTriangle(TriangleID tri) ONOEXCEPT;
            bool isTriangleInOctantBounds(TriangleID tri, OctantIndex octantID) ONOEXCEPT;

            // OctreeElements.cpp
            bool insertTriangle(TriangleID tri) ONOEXCEPT;
            bool updateTriangleInOctree(TriangleID tri) ONOEXCEPT;
            bool updateTrianglesInOctree(TriangleIDList tri) ONOEXCEPT;
            bool removeTriangleFromOctree(TriangleID tri) ONOEXCEPT;
            void octreeReinsertTriangles();
            void updateAffectedTriangles();

            // OctreeIntersection.cpp
            KeyList collectVerticesAroundCollisionOriginal(OctreeCollision collision, double range) ONOEXCEPT;
            TriangleIDList collectTrianglesAroundCollisionOriginal(OctreeCollision collision, double range) ONOEXCEPT;
            OctreeCollision octreeRayIntersectionOriginal(v3 origin, v3 direction) ONOEXCEPT;

            void collectVerticesAroundCollision(float range) ONOEXCEPT;
            void collectTrianglesAroundCollision(double range) ONOEXCEPT;
            void octreeRayIntersection(v3 origin, v3 direction) ONOEXCEPT;
            bool isOriginInOctantBounds(v3 origin, Octant octant) ONOEXCEPT;

            int mortonCodeHash(v3 point, v3 center) ONOEXCEPT; // returns the morton code position with respect to octant

            // List of octants which contain triangles
            // OctantIndexList activeOctants;

            OctantList octants;
            OctantList leaves;

            OctreeCollision collision;
            KeyList verticesInRange;
            TriangleIDList affectedTriangles;
            TriangleIDList trianglesInRange;

            // Plane normals may be wrong here, need to double check
            v3 planeNormals[3] = {
                {0, 0, 1}, // xy plane
                {1, 0, 0}, // yz plane
                {0, 1, 0}  // xz plane
            };
    };

} // namespace OctreeDefinition

#endif // Octree_HPP