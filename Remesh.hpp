#ifndef Remesh_HPP
#define Remesh_HPP
#include "MeshStats.hpp"
#include "Octree.hpp"
#include "SubdivisionSurface.hpp"
#include "Decimation.hpp"
#include <algorithm>
#include <execution>
#include <unordered_map>
#include <unordered_set>

namespace _Remesh
{
    using namespace OctreeDefinition;
    using namespace MeshStatsDefinition;
    using namespace Subdivision;
    using namespace _Decimation;

#define USING_REMESH_NO_EXCEPT

#ifndef USING_REMESH_NO_EXCEPT
#define REMNOEXCEPT
#else
#define REMNOEXCEPT noexcept
#endif

    class Remesh : public Decimation
    {
        public:
        void remesh(int nTimes) REMNOEXCEPT;
    };

} // namespace _Remesh

#endif // !Remesh_HPP