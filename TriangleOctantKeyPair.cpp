#include "TriangleOctantKeyPair.hpp"

using namespace TriangleOctantKeyPairDefinition;

TriangleOctantKeyPairDefinition::TriangleOctantKeyPair::TriangleOctantKeyPair()
{
}

TriangleOctantKeyPairDefinition::TriangleOctantKeyPair::TriangleOctantKeyPair(IndexedTrianglePosition triPosition, OctantIndex octIndex)
{
	this->triangleIndex = triPosition;
	this->octantIndex = octIndex;
}

TriangleOctantKeyPairDefinition::TriangleOctantKeyPair::~TriangleOctantKeyPair()
{
}
