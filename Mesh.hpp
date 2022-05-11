#ifndef Mesh_HPP
#define Mesh_HPP

#include "GraphicsData.hpp"
#include "TopologyComputation.hpp"
#include "MeshStats.hpp"

namespace MeshDefinition
{
	using namespace GraphicsDataDefinition;
	using namespace MeshStatsDefinition;
	using namespace TopologyComputationDefinition;

	class Mesh : public MeshStats
	{
		public:
			Construct Mesh();
			Deconstruct ~Mesh();

			KeyData searchLinear(rv3 direction, rv3 origin);

		// slot for edges
		// slot for Octree
		// slot for triangles
			string name;
			

	};
	typedef Mesh& MeshReference;  // reference to a mesh
	typedef Mesh* MeshPTR; // pointer to a mesh
}

#endif // Mesh_HPP
