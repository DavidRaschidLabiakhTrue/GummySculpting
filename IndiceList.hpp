#ifndef IndiceList_HPP
#define IndiceList_HPP

#include "Indices.hpp"

// Indices are to be used for PURELY LINEAR DRAWN STRUCTURES - such as rays and grids
namespace IndiceListDefinition
{
	using namespace IndicesDefinition;

	typedef vector<KeyData> Indices;

	// Container for Indices and indices *only*
	// NOT TO BE USED IN MESH, ONLY FOR LINEAR STRUCTURES SUCH AS GRID AND RAY
	class IndiceList
	{
	public:
		Construct IndiceList();
		Construct ~IndiceList();

		const int indicesMemorySize(); // return the size of the indices container * the size of the data type it contains.

		Indices indices;
	};
}

#endif
