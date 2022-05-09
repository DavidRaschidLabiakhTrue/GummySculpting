#include "TriangleList.hpp"

Usage TriangleListDefinition;

#ifdef IMPLEMENT_LINEAR_INDICES
IndiceList::IndiceList()
{
}

IndiceList::~IndiceList()
{
}
#endif


TriangleList::TriangleList()
{
}

TriangleList::~TriangleList()
{
}

const int TriangleList::indiceCount()
{
    return triangles.size() * 3;
}

const int TriangleList::triangleMemorySize()
{
	return triangles.size() * sizeof(IndexedTriangle);
}

void TriangleList::printTriangleListToConsole()
{
	forall(tri, triangles)
	{
		tri.print();
	}
	say "\n";
}


