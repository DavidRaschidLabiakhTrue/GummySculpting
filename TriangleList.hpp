#ifndef TriangleList_HPP
#define TriangleList_HPP

#include "Indices.hpp"
#include "IndexedTriangle.hpp"

namespace TriangleListDefinition
{
	using namespace IndicesDefinition;
	using namespace IndexedTriangleDefinition;

	using std::vector;

#ifdef IMPLEMENT_LINEAR_INDICES

	// UNUSED - COLLAPSE THIS

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

#endif

	typedef vector<IndexedTriangle> IndexedTriangles;


	/*
	*	OOP encapsulated format of indices to create triangles in a look up format.
	*	Inherited by - Graphics Data -> Mesh Stats -> Mesh
	*	Used to draw meshes via indices in opengl as well as provide direct look ups
	*/
	class TriangleList
	{
		public:
			TriangleList();
			~TriangleList();

			void printTriangleListToConsole();

			const int indiceCount(); // number of triangles * 3 == number of indices used to render
			const int triangleMemorySize(); // returns the memory size of triangles allocated
			IndexedTriangles triangles;


	};
}

#endif // TriangleList_HPP
