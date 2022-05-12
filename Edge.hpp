#ifndef Edge_HPP
#define Edge_HPP

#include "VertexLookUp.hpp"
#include <set>

namespace EdgeDefinition
{
	using namespace VertexLookUpDefinition;

	typedef vector<KeyData> VertexEdges;

	struct Edge
	{
		public:
			Edge();
			~Edge();
			void cleanUp(); // remove all duplicate edges that might occur during loading.
			void printEdge();
			bool touched = false;
			VertexEdges vertexEdges;
	};

	typedef Edge& EdgeReference; // edge reference
	

}

#endif
