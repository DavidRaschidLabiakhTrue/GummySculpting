#ifndef IndiceList_HPP
#define IndiceList_HPP

#include "Indices.hpp"
#include "IndexedTriangle.hpp"

namespace IndiceListDefinition
{
	using namespace IndicesDefinition;
	using namespace IndexedTriangleDefinition;

	using std::vector;

	typedef vector<KeyData> Indices;
	
	// Container for Indices - Will be expanded into Faces.
	// Inherited by GraphicsData->MeshStats->Mesh
	class IndiceList
	{
		public:
			Construct IndiceList();
			Construct ~IndiceList();

			Indices indices;
	};



	typedef vector<IndexedTriangle> IndexedTriangles;

	class TriangleList
	{
		public:
			TriangleList();
			~TriangleList();

			void printTriangleListToConsole();

			IndexedTriangles triangles;


	};
}

#endif
