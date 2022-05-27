#ifndef IndexedTriangle_HPP
#define IndexedTriangle_HPP

#include "Indices.hpp"

namespace IndexedTriangleDefinition
{
	using namespace IndicesDefinition;

#define USING_NOEXCEPT_TRIANGLE

#ifndef USING_NOEXCEPT_TRIANGLE
#define TRINOEXCEPT
#else
#define TRINOEXCEPT noexcept
#endif
	// Implementation of an Indexed Triangle meant for structured face look ups
	struct IndexedTriangle
	{
		public:

			IndexedTriangle();
			~IndexedTriangle();

			KeyData& operator[](const int pos) TRINOEXCEPT; // look up operator to directly access the underlying component of the indices

			void print(); // print the 3 indices in order to console
			KeyData indice[3]; // the actual key components - these values are fed straight into opengl to draw meshes by indice


	};

	typedef IndexedTriangle& RIndexTriangle;

	typedef int TriangleID;
	typedef vector<int> TriangleIDList;

}

#endif
