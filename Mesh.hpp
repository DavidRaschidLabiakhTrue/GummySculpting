#ifndef Mesh_HPP
#define Mesh_HPP

#include "GraphicsData.hpp"
#include "TopologyComputation.hpp"
#include "MeshStats.hpp"

#include "ITreeVisualization.hpp"

// #include "Octree.hpp" // too many issues 

namespace MeshDefinition
{
	using namespace GraphicsDataDefinition;
	using namespace MeshStatsDefinition;
	using namespace TopologyComputationDefinition;
	using namespace ITreeVisualizationDefinition;

	// a wrapper and container for all graphics and search structures used in the mesh.
	// contains graphics data for drawing
	// contains graphs and maps for searching.
	// meant as a final container for all 3d classes used for managing vertices and triangles ultimately.

	class Mesh : public ITreeVisualization
	{
		public:
			Mesh();
			~Mesh();

			void generateGraphsAndTrees();

			KeyData searchLinear(rv3 direction, rv3 origin);


			// slot for Octree

			string name;


	};
	typedef Mesh& MeshReference;  // reference to a mesh
	typedef Mesh* MeshPTR; // pointer to a mesh
}

#endif // Mesh_HPP
