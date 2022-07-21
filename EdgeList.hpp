#ifndef EdgeList_HPP
#define EdgeList_HPP

#include "Edge.hpp"
#include <unordered_set>

namespace EdgeListDefinition
{
	using namespace EdgeDefinition;


	typedef vector<Edge> Edges;
	typedef pair<KeyData, KeyData> EdgePair;

	// a class that contains a list of edges *by indice*
	/*
	*	edges[i] will return an edge that contains all *edges* to element i which also refers to the *vertex* in vertices[i]. It does not explicitly store the ID
	*/



	class EdgeList : public VertexLookUp
	{
		public:
			EdgeList();
			~EdgeList();

			EdgeReference getEdge(KeyData key) EDGENOEXCEPT;

			void generateEdges();

			void cleanUpEdges();

			void printAllEdges();

			const int edgesTotal() EDGENOEXCEPT;

			v3 averageAt(KeyData key) EDGENOEXCEPT;


			v4 colorAverageAt(KeyData key) EDGENOEXCEPT;

			KeyList getEdgeTriangles(EdgePair edge) EDGENOEXCEPT;
			KeyList getEdgeTriangles(KeyData v1, KeyData v2) EDGENOEXCEPT;

			Edges edges;



	};
}

#endif