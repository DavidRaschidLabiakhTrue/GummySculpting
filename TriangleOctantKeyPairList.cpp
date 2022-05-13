#include "TriangleOctantKeyPairList.hpp"

using namespace TriangleOctantKeyPairListDefinition;

TriangleOctantKeyPairListDefinition::TriangleOctantKeyPairList::TriangleOctantKeyPairList()
{
}

TriangleOctantKeyPairListDefinition::TriangleOctantKeyPairList::~TriangleOctantKeyPairList()
{
}

void TriangleOctantKeyPairListDefinition::TriangleOctantKeyPairList::loadTriangleOctantKeyPairList()
{
	const int triCount = totalTriangles();

	triangleToOctantList.reserve(triCount);

	for (int i = 0; i < triCount; i++)
	{
		triangleToOctantList.emplace_back(TriangleOctantKeyPair(i, -1));
	}


}
