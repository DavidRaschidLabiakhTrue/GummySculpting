#pragma once
#ifndef Octree_HPP
#define Octree_HPP

#include "MeshStats.hpp"
#include "Octant.hpp"
#include "OctreeCollision.hpp"
#include "OctreeStats.hpp"
#include "VertexIDHashing.hpp"

#include <unordered_set>

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

    class Octree : public OctreeStats
    {
        public:
            // Octree.cpp
            void buildOctree();
            void testOctree();
            void octreePrintStats();
            void resizeOctree(TriangleID tri);
            void clearOctree();
            void rebuildOctree();

            // OctreeOctant.cpp
            void subdivideOctant(OctantIndex octantID);
            void createChildOctant(OctantPosition octantPosition, OctantIndex parentIndex);
            OctantIndex findOctantForTriangle(TriangleID tri);
            bool isTriangleInOctantBounds(TriangleID tri, OctantIndex octantID);

            // OctreeElements.cpp
            bool insertTriangle(TriangleID tri);
            bool updateTriangleInOctree(TriangleID tri);
            bool updateTrianglesInOctree(TriangleIDList tri);
            bool removeTriangleFromOctree(TriangleID tri);

            // OctreeIntersection.cpp
            KeyList collectVerticesAroundCollision(OctreeCollision collision, double range);
            OctreeCollision octreeRayIntersection(v3 origin, v3 direction);

            int mortonCodeHash(v3 point, v3 center); // returns the morton code position with respect to octant

            // List of octants which contain triangles
            // OctantIndexList activeOctants;

            OctantList octants;
            OctantList leaves;

            // Plane normals may be wrong here, need to double check
            v3 planeNormals[3] = {
                {0, 0, 1}, // xy plane
                {1, 0, 0}, // yz plane
                {0, 1, 0}  // xz plane
            };
    };

} // namespace OctreeDefinition

/*

//David: Obscure Action occuring - Ignoring
struct point_hash
{
        std::size_t operator()(const Point &p) const
        {
            return std::hash<int>()(p.index);
            // V3 pos = VertexLookUp(p.index);
            // return (size_t)((int)(pos.x * 1000) ^ (int)(pos.y * 100) ^ (int)(pos.z * 10));
        }
};
//David: Obscure Action occuring - Ignoring
struct point_equal
{
        bool operator()(const Point &p1, const Point &p2) const
        {
            return p1.index == p2.index;
        }
};
*/
#endif // Octree_HPP