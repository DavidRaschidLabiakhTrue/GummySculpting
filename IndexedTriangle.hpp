#ifndef IndexedTriangle_HPP
#define IndexedTriangle_HPP

#include "Indices.hpp"

namespace IndexedTriangleDefinition
{
	using namespace IndicesDefinition;
	struct IndexedTriangle
	{
		public:
			IndexedTriangle();
			~IndexedTriangle();
			KeyData indice[3];
	};
}

#endif
