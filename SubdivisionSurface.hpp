#ifndef SubdivisionSurface_HPP
#define SubdivisionSurface_HPP
#include "Octree.hpp"
#include "MeshStats.hpp"
#include "OctreeVisualization.hpp"
#include <unordered_map>

namespace Subdivision
{
    using namespace OctreeDefinition;
    using namespace MeshStatsDefinition;
    using namespace OctreeVisualizationDefinition;

    #define InfiniteCreaseAngle std::numeric_limits<float>::max()
    #define PI 3.141592f
    #define TWO_PI 6.283184f
    class SubdivisionSurface : public OctreeVisualization
    {
        public:
            void loopSubdivision(int level = 1, bool rebuildRefresh = true);
            inline v3 getEdgeMidpoint(KeyData v1, KeyData v2);
            void subdivisionTest();
            float getBeta(int nEdges);
            v3 sumNeighbors(unordered_set<KeyData> neighbors);
            bool isVertexOnCrease(KeyData vertexID);
            float getCreaseAngleOfNewVertex(KeyData vertexID);
            void simpleSubdivision4to1(int level = 1, bool octreeRebuild = true, bool refreshDisplay = true);

            int vertexOffset;
            float angleLimit = 1.5708f; // Radians, 90 degrees
    };


} // namespace Subdivision

#endif // !SubdivisionSurface_HPP