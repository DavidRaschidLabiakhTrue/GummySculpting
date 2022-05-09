#include "TriangleList.hpp"

Usage TriangleListDefinition;




TriangleList::TriangleList()
{

}

TriangleList::~TriangleList()
{

}

const int TriangleList::triangleCountAsindiceCount()
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


