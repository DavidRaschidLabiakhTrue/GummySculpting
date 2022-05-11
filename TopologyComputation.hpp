#ifndef TopologyComputation_HPP
#define TopologyComputation_HPP

#include "V3D.hpp"

namespace TopologyComputationDefinition
{
	using namespace VertexDefinition;

	bool intersectionMoller(rv3 origin, rv3 direction, rv3 p0, rv3 p1, rv3 p2, rv3 intersectionPoint);


}

#endif
