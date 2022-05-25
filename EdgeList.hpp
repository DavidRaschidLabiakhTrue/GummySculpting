#ifndef EdgeList_HPP
#define EdgeList_HPP

#include "Edge.hpp"


namespace EdgeListDefinition
{
	using namespace EdgeDefinition;


	typedef vector<Edge> Edges;

	// a class that contains a list of edges *by indice*
	/*
	*	edges[i] will return an edge that contains all *edges* to element i which also refers to the *vertex* in vertices[i]. It does not explicitly store the ID
	*/

	class EdgeList : public VertexLookUp
	{
		public:
			EdgeList();
			~EdgeList();

			EdgeReference getEdge(KeyData key);

			void generateEdges();

			void cleanUpEdges();

			void printAllEdges();

			const int edgesTotal();

			v3 averageAt(KeyData key); // 

			v4 colorAverageAt(KeyData key);


			

			Edges edges;



	};
}

#endif