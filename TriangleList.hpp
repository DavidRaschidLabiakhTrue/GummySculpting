#ifndef TriangleList_HPP
#define TriangleList_HPP

#include "Indices.hpp"
#include "IndexedTriangle.hpp"

namespace TriangleListDefinition
{
	using namespace IndicesDefinition;
	using namespace IndexedTriangleDefinition;

	using std::vector;


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

			const int triangleCountAsindiceCount(); // number of triangles * 3 == number of indices used to render
			const int triangleMemorySize(); // returns the memory size of triangles allocated
			IndexedTriangles triangles;


	};
}

#endif // TriangleList_HPP
