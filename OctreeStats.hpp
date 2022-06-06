#ifndef OctreeStats_HPP
#define OctreeStats_HPP

#include "MeshStats.hpp"
#include "TriangleOctantKeyPairList.hpp"

namespace OctreeStatsDefinition
{
    using namespace MeshStatsDefinition;
    using namespace TriangleOctantKeyPairListDefinition;

    class OctreeStats : public MeshStats
    {
        public:
            int octantTriangleLimit = 1000; // Max triangles per octant
            int octreeDepthLimit = 10;      // Max depth of octree
            int octreeDepth = 0;            // Depth of octree
            float octreeBuffer = 1.5f;      // Adds buffer to root bounds
            float octreeLooseness = 1.1f;   // Looseness of octant bounds to allow overlap at borders
            int octreeCurrentDepth = 0;     // Temp value to track current depth functions operate at
            OctantIndex root = 0;           // Root octant index (Always 0, should define or make constant)
    };
} // namespace OctreeStatsDefinition

#endif
