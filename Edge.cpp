#include "Edge.hpp"

using namespace EdgeDefinition;

EdgeDefinition::Edge::Edge()
{
}

EdgeDefinition::Edge::~Edge()
{
}

void EdgeDefinition::Edge::cleanUp()
{
	using std::set;

	set<KeyData> keys;
	const auto sizeofedges = this->vertexEdges.size();

	for (int i = 0; i < sizeofedges; i++)
	{
		keys.insert(this->vertexEdges[i]);
	}
	vertexEdges.assign(keys.begin(), keys.end());

}

void EdgeDefinition::Edge::printEdge()
{
	forall(key, vertexEdges)
	{
		say key << ' ';
	}
	say "\n";
}