#include "IndiceList.hpp"

Usage IndiceListDefinition;

IndiceList::IndiceList()
{
}

IndiceList::~IndiceList()
{
}

TriangleList::TriangleList()
{
}

TriangleList::~TriangleList()
{
}

void TriangleList::printTriangleListToConsole()
{
	forall(tri, triangles)
	{
		tri.print();
	}
	say "\n";
}


