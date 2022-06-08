#ifndef SubdivisionSurface_HPP
#define SubdivisionSurface_HPP
#include "Octree.hpp"
#include "MeshStats.hpp"
#include "OctreeVisualization.hpp"
#include <unordered_map>
#include <execution>
#include <algorithm>


namespace Subdivision
{
    using namespace OctreeDefinition;
    using namespace MeshStatsDefinition;
    using namespace OctreeVisualizationDefinition;

    #define InfiniteCreaseAngle std::numeric_limits<float>::max()
    // #define PI 3.141592f
    #define TWO_PI 6.283184f

#define USING_SUBDIVISION_NO_EXCEPT

#ifndef USING_SUBDIVISION_NO_EXCEPT
#define SUBNOEXCEPT
#else
#define SUBNOEXCEPT noexcept
#endif


    class SubdivisionSurface : public OctreeVisualization
    {
        public:
            void loopSubdivision(int level = 1, bool rebuildRefresh = true) SUBNOEXCEPT;
            inline v3 getEdgeMidpoint(KeyData v1, KeyData v2) SUBNOEXCEPT;
            void subdivisionTest() SUBNOEXCEPT;
            float getBeta(int nEdges) SUBNOEXCEPT;
            v3 sumNeighbors(unordered_set<KeyData> neighbors) SUBNOEXCEPT;
            bool isVertexOnCrease(KeyData vertexID) SUBNOEXCEPT;
            float getCreaseAngleOfNewVertex(KeyData vertexID) SUBNOEXCEPT;
            void simpleSubdivision4to1(int level = 1, bool octreeRebuild = true, bool refreshDisplay = true) SUBNOEXCEPT;
            void gotoSubdivisionLevel(int level) SUBNOEXCEPT;

            int vertexOffset;
            float angleLimit = 1.5708f; // Radians, 90 degrees

            int currentSubdivisionLevel = 0;
            vector<Edges> edgeLists;
            vector<int> vertexOffsets;
            vector<IndexedTriangles> triangleLists;
    };


} // namespace Subdivision

#endif // !SubdivisionSurface_HPP