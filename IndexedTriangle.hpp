#ifndef IndexedTriangle_HPP
#define IndexedTriangle_HPP

#include "Indices.hpp"

namespace IndexedTriangleDefinition
{
	using namespace IndicesDefinition;

	// Implementation of an Indexed Triangle meant for structured face look ups

	#pragma pack()
	struct IndexedTriangle
	{
		public:

			IndexedTriangle();
			~IndexedTriangle();

			void print();
			KeyData indice[3];
	};

}

#endif
