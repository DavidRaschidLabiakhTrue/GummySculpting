#ifndef Edge_HPP
#define Edge_HPP

#include "VertexLookUp.hpp"
#include <set>
#include <unordered_set>

namespace EdgeDefinition
{
	using namespace VertexLookUpDefinition;

	typedef unordered_set<KeyData> VertexEdges;

	// container for Edge IDs that correspond to a vertex list.
	struct Edge
	{
		public:
			Edge();
			~Edge();
			void cleanUp(); // remove all duplicate edges that might occur during loading.
			void printEdge(); // print the edge to console

			bool touched = false;
			VertexEdges vertexEdges;
	};

	typedef Edge& EdgeReference; // edge reference


}

#endif
