#ifndef SubdivisionSurface_HPP
#define SubdivisionSurface_HPP
#include "Octree.hpp"
#include "MeshStats.hpp"
#include <unordered_map>

namespace Subdivision
{
    using namespace OctreeDefinition;
    using namespace MeshStatsDefinition;

    #define InfiniteCreaseAngle std::numeric_limits<float>::max()
    #define PI 3.141592f
    #define TWO_PI 6.283184f
    class SubdivisionSurface : public Octree
    {
        public:
            int simpleSubdivision4to1();
            void loopSubdivision();
            inline v3 getEdgeMidpoint(KeyData v1, KeyData v2);
            void subdivisionTest();
            float getBeta(int nEdges);
            v3 sumNeighbors(unordered_set<KeyData> neighbors);
            bool isVertexOnCrease(KeyData vertexID);
            float getCreaseAngleOfNewVertex(KeyData vertexID);

            int vertexOffset;
            float angleLimit = 1.5708f; // Radians, 90 degrees
    };


} // namespace Subdivision

#endif // !SubdivisionSurface_HPP