#ifndef IndiceList_HPP
#define IndiceList_HPP

#include "Indices.hpp"

// Indices are to be used for PURELY LINEAR DRAWN STRUCTURES - such as rays and grids
namespace IndiceListDefinition
{
	using namespace IndicesDefinition;

	typedef vector<KeyData> Indices;

	// Container for Indices - Will be expanded into Faces.
	// Inherited by GraphicsData->MeshStats->Mesh
	class IndiceList
	{
	public:
		Construct IndiceList();
		Construct ~IndiceList();

		const int indicesMemorySize();

		Indices indices;
	};
}

#endif
