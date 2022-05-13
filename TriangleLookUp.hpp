#ifndef TriangleLookUp_HPP
#define TriangleLookUp_HPP

#include "EdgeList.hpp"
#include "LinearAlgebra.hpp"
namespace TriangleLookUpDefinition
{
	using namespace EdgeListDefinition;
	using namespace LinearAlgebra;

	// a look up implementation that wraps triangle operations to be inherited into the mesh class
	class TriangleLookUp : public EdgeList
	{
		public:
		TriangleLookUp();
		~TriangleLookUp();

		v3 getTriangleNormal(KeyData key); // compute the normal from a given key corresponding to a *triangle*

	};
}

#endif // !TriangleLookUp_HPP

