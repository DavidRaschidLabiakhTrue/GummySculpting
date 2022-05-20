#ifndef SubdivisionSurface_HPP
#define SubdivisionSurface_HPP
#include "Octree.hpp"
#include <unordered_map>

namespace Subdivision
{
    using namespace OctreeDefinition;
    using namespace MeshStatsDefinition;
    class SubdivisionSurface : public Octree
    {
        public:
            void simpleSubdivision4to1();
            void loopSubdivision();
            v3 getEdgeMidpoint(KeyData v1, KeyData v2);
            void subdivisionTest();
    };
} // namespace Subdivision

#endif // !SubdivisionSurface_HPP