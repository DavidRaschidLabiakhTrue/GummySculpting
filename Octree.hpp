#ifndef Octree_HPP
#define Octree_HPP

#include "MeshStats.hpp"
#include "OctreeStats.hpp"

#include "Octant.hpp"
#include "OctreeCollision.hpp"

#include <unordered_set>

namespace OctreeDefinition
{
    using namespace MeshStatsDefinition;   // this is all that's needed as it auto includes everything it needs and uses
    using namespace OctreeStatsDefinition; // decoupling
    using namespace OctantDefinition;
	using namespace OctreeCollisionDefinition; // I am using collision
	using std::unordered_set;

	typedef unordered_set<OctantIndex> OctantLeavesList;


    class Octree : public OctreeStats
    {
        public:
            Octree();
            ~Octree();

            void buildOctree();
            void octreePrintStats();

            bool octantPointsInBound(RIndexTriangle tri, OctantIndex octantID);

            void octreeUpdate(int t);
            void octreeUpdate(TriangleList& tris);

			const int octantsTotal();
			const int octantsLeavesTotal();

			auto collect(OctreeCollision& collision, double range); // auto return until return type is determined

	

            OctantList octants;
			OctantLeavesList leaves;

    };

} // namespace OctreeDefinition

#endif

// Fixing

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


/*
class Octree : public MeshStats
{
    public:
        // EMPTY CONSTRUCTOR TO SILENCE C++.
        Octree();
        ~Octree();

        double tempLooseVal = 0;

        int limit = 1000;
        int depthLimit = 10;
        int depth = 0;
        double looseness = 0.2;
        int currentDepth = 0;
        vector<Octant> octants;
        unordered_set<int> leaves;
        vector<Point> points;
        vector<GEdge> edges;
        unordered_set<GEdge, edge_hash, edge_equal> edgeset;
        vector<Triangle> triangles;
        vector<v3> octreeVertices;
        vector<int> octreeIndices;


        Octree(vector<v3> &verts, vector<int> &indices);
        int findOctant(int t);
        int getNext(int o, int t);
        bool insert(int t);
        bool contains(Triangle t);
        bool remove(Triangle &t);
        vector<Point> collect(Collision &collision, double range);
        void resize(int t);
        Octant createParent(vec3 direction);
        Collision rayIntersection(v3 &origin, v3 direction);
        void octreeDebug();
        void subdivideOctant(int o);
        void generateMesh(bool trianglesOnly);
};

#endif
*/