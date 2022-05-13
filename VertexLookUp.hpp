#ifndef VertexLookUp_HPP
#define VertexLookUp_HPP

#include "VertexList.hpp"
#include "TriangleList.hpp"

#include "TopologyComputation.hpp"

namespace VertexLookUpDefinition
{
	using namespace VertexListDefinition;
	using namespace TriangleListDefinition;
	using namespace TopologyComputationDefinition;


	// a class that implements vertex look up mechanics that is inherited into mesh.
	class VertexLookUp : public VertexList, public TriangleList
	{
		public:
			VertexLookUp();
			~VertexLookUp();
			KeyData closest(rv3 pointToTest, RIndexTriangle tri);
			RV3D lookUpV3D(KeyData key);
			RIndexTriangle lookUpTriangle(KeyData key);
			KeyData findClosest(rv3 testpoint, KeyData p0, KeyData p1, KeyData p2);
	};
}


#endif
