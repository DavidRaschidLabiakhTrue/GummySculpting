#ifndef Octant_HPP
#define Octant_HPP

#include "MeshStats.hpp"
#include "TriangleOctantKeyPairList.hpp"

namespace OctantDefinition
{
	using namespace MeshStatsDefinition;
	using namespace TriangleOctantKeyPairListDefinition;

	typedef int ChildArray;
	typedef int OctantParent;

	struct Octant;

	// ^ This is forward declare to allow for this below typedef which is used in Octant::subdivide

	typedef vector<Octant> OctantList; // list of octants
	// typedef unordered_set<OctantIndex> OctantIndexList; // list of octant IDs

#define NoOctantParentSet -1
#define NoOctantChildSet -1
#define NonExistentOctantIndex -1

	enum OctantState
	{
		OctantEmptyInternal = 0,
		OctantNotEmptyInternal = 1,
		OctantLeaf = 2
	};

	enum OctantPosition
	{
		BottomBackLeft = 0,
		BottomFrontLeft = 1,
		TopBackLeft = 2,
		TopFrontLeft = 3,
		BottomBackRight = 4,
		BottomFrontRight = 5,
		TopBackRight = 6,
		TopFrontRight = 7
	};

	const vector<v3> octantPositionVectors =
	{
		v3(-1, -1, -1), // BottomBackLeft
		v3(-1, -1, 1),  // BottomFrontLeft
		v3(-1, 1, -1),  // TopBackLeft
		v3(-1, 1, 1),   // TopFrontLeft
		v3(1, -1, -1),  // BottomBackRight
		v3(1, -1, 1),   // BottomFrontRight
		v3(1, 1, -1),   // TopBackRight
		v3(1, 1, 1)     // TopFrontRight
	};


    /*
     *	To be used in Octree - Data Container for 3d data
     */
    struct Octant
    {
            OctantIndex octantIndex;                 // store octant index on the octant itself.
            TriangleIDList triangleIDs;              // references to positions within the triangle array
            OctantParent parent = NoOctantParentSet; // integer id to parent within octant list
            ChildArray children[8] = {               // integer IDs to octant children within the OctantList
                NoOctantChildSet,
                NoOctantChildSet,
                NoOctantChildSet,
                NoOctantChildSet,
                NoOctantChildSet,
                NoOctantChildSet,
                NoOctantChildSet,
                NoOctantChildSet};
            float octantHalfSize;                 // HalfSize of the octant
            v3 octantCenter;                      // center position of octant
            OctantState octantState = OctantLeaf; // State of the octant. Default = OctantLeaf
    };

    typedef Octant &OctantReference;

} // namespace OctantDefinition

#endif // !Octant_HPP