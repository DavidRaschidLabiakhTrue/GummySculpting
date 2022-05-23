#ifndef Mesh_HPP
#define Mesh_HPP

#include "GraphicsData.hpp"
#include "TopologyComputation.hpp"
#include "MeshStats.hpp"

#include "ITreeVisualization.hpp"

#include "Octree.hpp"
#include "SubdivisionSurface.hpp"

#include "MeshChangeLog.hpp"
#include <variant>
#include <unordered_map>
#include <functional>

// #include "Octree.hpp" // too many issues

namespace MeshDefinition
{
	using namespace GraphicsDataDefinition;
	using namespace MeshStatsDefinition;
	using namespace TopologyComputationDefinition;
	using namespace ITreeVisualizationDefinition;

	using namespace OctreeDefinition;
	using namespace Subdivision;
	using namespace MeshChangeLogDefinition;


	// a wrapper and container for all graphics and search structures used in the mesh.
	// contains graphics data for drawing
	// contains graphs and maps for searching.
	// meant as a final container for all 3d classes used for managing vertices and triangles ultimately.

	class Mesh : public SubdivisionSurface //public ITreeVisualization
	{
		public:
			Mesh();
			~Mesh();

			void generateGraphsAndTrees();

			KeyData searchLinear(rv3 direction, rv3 origin);

			void revertHistory();

			void forwardHistory();

			void cullHistory(ChangeLogLevel levelsUpwardToCull);
			void createVariableMap();




			ChangeLog history; // mesh reversion history.

			// slot for Octree

			string name;

			unordered_map<string, variant<reference_wrapper<int>, reference_wrapper<float>>> meshVariables;

	};
	typedef Mesh& MeshReference;  // reference to a mesh
	typedef Mesh* MeshPTR; // pointer to a mesh
}

#endif // Mesh_HPP
