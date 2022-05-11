#ifndef IndexedTriangle_HPP
#define IndexedTriangle_HPP

#include "Indices.hpp"

namespace IndexedTriangleDefinition
{
	using namespace IndicesDefinition;

	// Implementation of an Indexed Triangle meant for structured face look ups

	
	struct IndexedTriangle
	{
		public:

			IndexedTriangle();
			~IndexedTriangle();

			KeyData& operator[](int pos);

			void print();
			KeyData indice[3];
	};

	typedef IndexedTriangle& RIndexTriangle;

}

#endif
