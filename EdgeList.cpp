#include "EdgeList.hpp"

using namespace EdgeListDefinition;

EdgeList::EdgeList()
{
}

EdgeList::~EdgeList()
{
}

EdgeReference EdgeList::getEdge(KeyData key)
{
	return this->edges[key];
}

void EdgeList::generateEdges()
{
	const auto countUniqueVertices = vertices.size();
	edges.reserve(countUniqueVertices);
	for (int i = 0; i < countUniqueVertices; i++)
	{
		this->edges.emplace_back(Edge());
	}

	forall(tri, triangles)
	{
		edges[tri[0]].vertexEdges.emplace_back(tri[1]);
		edges[tri[0]].vertexEdges.emplace_back(tri[2]);

		edges[tri[1]].vertexEdges.emplace_back(tri[0]);
		edges[tri[1]].vertexEdges.emplace_back(tri[2]);

		edges[tri[2]].vertexEdges.emplace_back(tri[0]);
		edges[tri[2]].vertexEdges.emplace_back(tri[1]);
	}

	this->cleanUpEdges();
	//printAllEdges();
}

void EdgeList::cleanUpEdges()
{
	const auto countofedges = edges.size();

	for (int i = 0; i < countofedges; i++)
	{
		edges[i].cleanUp();
	}
}

void EdgeList::printAllEdges()
{
	int tracker = 0;
	const int edgeCount = edges.size();

	for (int i = 0; i < edgeCount; i++)
	{
		say "id:" spc tracker << ":";
		tracker++;
		edges[i].printEdge();
	}

}

const int EdgeListDefinition::EdgeList::edgesTotal()
{
    return edges.size();
}

v3 EdgeListDefinition::EdgeList::averageAt(KeyData key)
{
	v3 res = v3(0);

	auto& edge = edges[key].vertexEdges;

	forall(element, edge)
	{
		res += vertices[element].position;
	}
	res /= (float)edge.size();
	
	return res;
}
