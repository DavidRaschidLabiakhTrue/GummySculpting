#ifndef EdgeList_HPP
#define EdgeList_HPP

#include "Edge.hpp"


namespace EdgeListDefinition
{
	using namespace EdgeDefinition;


	typedef vector<Edge> Edges;

	class EdgeList : public VertexLookUp
	{
		public:
			EdgeList();
			~EdgeList();

			EdgeReference getEdge(KeyData key);

			void generateEdges();

			void cleanUpEdges();

			void printAllEdges();


			

			Edges edges;



	};
}

#endif