
#ifndef Decimation_HPP
#define Decimation_HPP
#include "MeshStats.hpp"
#include "Octree.hpp"
#include "SubdivisionSurface.hpp"
#include <algorithm>
#include <execution>
#include <unordered_map>

namespace _Decimation
{
    using namespace OctreeDefinition;
    using namespace MeshStatsDefinition;
    using namespace Subdivision;

#define USING_DECIMATION_NO_EXCEPT

#ifndef USING_DECIMATION_NO_EXCEPT
#define DECNOEXCEPT
#else
#define DECNOEXCEPT noexcept
#endif

    // maybe don't use tuple? pair is faster, but needs to work with pq
    typedef tuple<float, KeyData, KeyData> EdgeTuple;
    typedef priority_queue<EdgeTuple, vector<EdgeTuple>, greater<EdgeTuple>> EdgePQ;
    class Decimation : public SubdivisionSurface
    {
        public:
            void decimateMesh(float percentage = 0.25f) DECNOEXCEPT;
            EdgePQ parameterizeEdges() DECNOEXCEPT;
            KeyList collapseEdge(EdgePair edge) DECNOEXCEPT;
            void collapseTriangle(KeyData tri) DECNOEXCEPT;
            void removeTriangle(KeyData tri, bool skipResize = false, int replacement = -1) DECNOEXCEPT; // remove triangle from the list.
            void removeTriangles(KeyList triList) DECNOEXCEPT;                                           // removes triangles from the list
            void removeVertex(KeyData vertexID) DECNOEXCEPT;
            void removeVertices(set<KeyData, greater<KeyData>> vertexSet) DECNOEXCEPT;
            void verifyMesh();
    };

} // namespace _Decimation

#endif // !Decimation_HPP