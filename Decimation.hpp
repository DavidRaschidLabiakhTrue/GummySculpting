
#ifndef Decimation_HPP
#define Decimation_HPP
#include "MeshStats.hpp"
#include "Octree.hpp"
#include "SubdivisionSurface.hpp"
#include <algorithm>
#include <execution>
#include <unordered_map>
#include <unordered_set>

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

    struct pair_hash
    {
            inline std::size_t operator()(const std::pair<int, int> &v) const
            {
                return v.first * 31 + v.second;
            }
    };

    struct hash_tuple
    {

            template <class T1, class T2, class T3>

            size_t operator()(
                const tuple<T1, T2, T3> &x)
                const
            {
                return get<0>(x) ^ get<1>(x) ^ get<2>(x);
            }
    };

    typedef pair<float, EdgePair> DistEdgePair;
    typedef priority_queue<DistEdgePair, vector<DistEdgePair>, greater<DistEdgePair>> EdgePQ;
    class Decimation : public SubdivisionSurface
    {
        public:
            void decimateMesh(float percentage = 0.25f) DECNOEXCEPT;
            EdgePQ parameterizeEdges() DECNOEXCEPT;
            void parameterizeVertexEdges(KeyData vertexID, EdgePQ &pq) DECNOEXCEPT;
            void collapseEdge(EdgePair edge) DECNOEXCEPT;
            void swapTriangles(KeyData tri1, KeyData tri2) DECNOEXCEPT;
            void deleteTriangle(KeyData tri) DECNOEXCEPT;          // remove triangle from the list.                                        // removes triangles from the list
            void swapVertices(KeyData v1, KeyData v2) DECNOEXCEPT; // swap vertices in the list.                                     // swaps vertices in the list
            void deleteVertex(KeyData vertexID) DECNOEXCEPT;
            void verifyMesh();
            bool doesEdgeExist(KeyData v1, KeyData v2) DECNOEXCEPT;
    };

} // namespace _Decimation

#endif // !Decimation_HPP