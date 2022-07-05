#pragma once
#ifndef Octree_HPP
#define Octree_HPP

#include "MeshStats.hpp"
#include "Octant.hpp"
#include "OctreeCollision.hpp"
#include "OctreeStats.hpp"
#include "VertexIDHashing.hpp"

#include <chrono>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_set>
#include <concurrent_vector.h>
#include <concurrent_unordered_set.h>
#include <concurrent_queue.h>
#include <random>

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
            void loadTriangleOctantList() ONOEXCEPT;

            // Parallel Octree functions
            void resizeOctreeParallel(TriangleID tri) ONOEXCEPT;

            // OctreeOctant.cpp
            void subdivideOctant(OctantIndex octantID) ONOEXCEPT;
            void createChildOctant(OctantPosition octantPosition, OctantIndex parentIndex) ONOEXCEPT;
            OctantIndex findOctantForTriangle(TriangleID tri) ONOEXCEPT;
            bool isTriangleInOctantBounds(TriangleID tri, OctantIndex octantID) ONOEXCEPT;

            // Parallel Octant Functions
            OctantIndex insertOctantParallel(OctantReference octant) ONOEXCEPT;
            OctantIndex createChildOctantParallel(OctantPosition octantPosition, OctantIndex parentIndex) ONOEXCEPT;
            void subdivideOctantParallel(OctantIndex oix, int localDepth) ONOEXCEPT;
            pair<OctantIndex, int> findOctantForTriangleParallel(TriangleID triangle, OctantIndex start) ONOEXCEPT;

            // OctreeElements.cpp
            bool insertTriangle(TriangleID tri) ONOEXCEPT;
            bool insertTriangles() ONOEXCEPT;
            bool updateTriangleInOctree(TriangleID tri) ONOEXCEPT;
            bool updateTrianglesInOctree(TriangleIDList tris) ONOEXCEPT;
            bool removeTriangleFromOctree(TriangleID tri) ONOEXCEPT;
            void octreeReinsertTriangles();
            void updateAffectedTriangles();
            void clearCollision() ONOEXCEPT;

            // Parallel OctreeElements functions
            bool insertTriangleParallel(TriangleID tri) ONOEXCEPT;
            bool insertTrianglesParallel() ONOEXCEPT;
            void octreeReinsertTrianglesParallel() ONOEXCEPT;
            bool updateTriangleInOctreeParallel(TriangleID tri) ONOEXCEPT;
            bool updateTrianglesInOctreeParallel(TriangleIDList tris) ONOEXCEPT;
            bool removeTriangleFromOctreeParallel(TriangleID tri) ONOEXCEPT;
            void updateAffectedTrianglesParallel() ONOEXCEPT;

            // OctreeIntersection.cpp
            KeyList collectVerticesAroundCollisionOriginal(OctreeCollision collision, float range) ONOEXCEPT;
            TriangleIDList collectTrianglesAroundCollisionOriginal(OctreeCollision collision, float range) ONOEXCEPT;
            OctreeCollision octreeRayIntersectionOriginal(v3 origin, v3 direction) ONOEXCEPT;

            void collectVerticesAroundCollision(float range) ONOEXCEPT;
            void collectTrianglesAroundCollision(float range) ONOEXCEPT;

            void octreeRayIntersectionCore(v3 origin, v3 direction, OctreeCollision& collisionRef) ONOEXCEPT;
            void octreeRayIntersection(v3 origin, v3 direction, bool isSymmetric = false, v3 planeOrigin = v3(0), v3 planeNormal = v3(1,0,0)) ONOEXCEPT;
            bool isOriginInOctantBounds(v3 origin, OctantReference octant) ONOEXCEPT;
            void reflectRay(rv3 origin, rv3 direction, rv3 planeOrigin, rv3 planeNormal, rv3 reflectOrigin, rv3 reflectDirection) ONOEXCEPT;

            void collectAroundCollision(float range, bool collectAffectedTriangles = true, bool collectTrianglesInRange = false, bool isSymmetric = false) ONOEXCEPT;
            void collectVerticesWithReflection(float range) ONOEXCEPT;

            int mortonCodeHash(v3 point, v3 center) ONOEXCEPT; // returns the morton code position with respect to octant

            // List of octants which contain triangles
            // OctantIndexList activeOctants;

            concurrency::concurrent_vector<Octant> octants;
            // OctantList octants;
            // OctantList leaves;

            OctreeCollision collision;
            KeyList verticesInRange;
            TriangleIDList affectedTriangles;
            TriangleIDList trianglesInRange;

            OctreeCollision reflectedCollision;
            KeyList reflectedVerticesInRange;
            TriangleIDList reflectedTrianglesInRange;

            concurrency::concurrent_vector<OctantIndex> triangleToOctantList;

            // Plane normals may be wrong here, need to double check
            v3 planeNormals[3] = {
                {0, 0, 1}, // xy plane
                {1, 0, 0}, // yz plane
                {0, 1, 0}  // xz plane
            };
    };

} // namespace OctreeDefinition
#endif // Octree_HPP