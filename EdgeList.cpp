#include "EdgeList.hpp"

using namespace EdgeListDefinition;

EdgeListDefinition::EdgeList::EdgeList()
{
}

EdgeListDefinition::EdgeList::~EdgeList()
{
}

EdgeReference EdgeListDefinition::EdgeList::getEdge(KeyData key)
{
	return this->edges[key];
}

void EdgeListDefinition::EdgeList::generateEdges()
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

	cleanUpEdges();
}

void EdgeListDefinition::EdgeList::cleanUpEdges()
{
	const auto countofedges = edges.size();

	for (int i = 0; i < countofedges; i++)
	{
		edges[i].cleanUp();
	}
}
