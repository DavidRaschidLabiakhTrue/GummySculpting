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
	edges.clear();
	const auto countUniqueVertices = vertices.size();
	edges.reserve(countUniqueVertices);
	for (int i = 0; i < countUniqueVertices; i++)
	{
		this->edges.emplace_back(Edge());
	}

	forall(tri, triangles)
	{
		edges[tri[0]].vertexEdges.insert(tri[1]);
		edges[tri[0]].vertexEdges.insert(tri[2]);

		edges[tri[1]].vertexEdges.insert(tri[0]);
		edges[tri[1]].vertexEdges.insert(tri[2]);

		edges[tri[2]].vertexEdges.insert(tri[0]);
		edges[tri[2]].vertexEdges.insert(tri[1]);
	}

	// easier parallelizable version
	// for(int vertexID = 0; vertexID < vertices.size(); vertexID++) {
	// 	foreach(tri, vertices[vertexID].triangleIDs) {
	// 		if(triangles[tri][0] == vertexID){
	// 			edges[vertexID].vertexEdges.insert(triangles[tri][1]);
	// 			edges[vertexID].vertexEdges.insert(triangles[tri][2]);
	// 		} else if (triangles[tri][1] == vertexID) {
	// 			edges[vertexID].vertexEdges.insert(triangles[tri][0]);
	// 			edges[vertexID].vertexEdges.insert(triangles[tri][2]);
	// 		} else if (triangles[tri][2] == vertexID) {
	// 			edges[vertexID].vertexEdges.insert(triangles[tri][0]);
	// 			edges[vertexID].vertexEdges.insert(triangles[tri][1]);
	// 		}
	// 	}
	// }

	// this->cleanUpEdges();
	//printAllEdges();
}

void EdgeList::cleanUpEdges()
{
	const auto countofedges = edges.size();

	for (int i = 0; i < countofedges; i++)
	{
		// edges[i].cleanUp();
	}
}

void EdgeList::printAllEdges()
{
	int tracker = 0;
	const int edgeCount = (const int) edges.size();

	for (int i = 0; i < edgeCount; i++)
	{
		say "id:" spc tracker << ":";
		tracker++;
		edges[i].printEdge();
	}

}

const int EdgeListDefinition::EdgeList::edgesTotal()
{
    return (const int) edges.size();
}

v4 EdgeListDefinition::EdgeList::colorAverageAt(KeyData key)
{
	v4 res = v4(0);

	auto& edge = edges[key].vertexEdges;

	forall(element, edge)
	{
		res += vertices[element].color;
	}
	res /= (float)edge.size();

    return res;
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
