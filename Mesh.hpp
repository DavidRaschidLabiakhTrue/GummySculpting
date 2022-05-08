#ifndef Mesh_HPP
#define Mesh_HPP

#include "GraphicsData.hpp"
#include "MeshStats.hpp"

namespace MeshDefinition
{
	Usage GraphicsDataDefinition;
	Usage MeshStatsDefinition;
	class Mesh : public MeshStats
	{
		public:
			Construct Mesh();
			Deconstruct ~Mesh();
		// slot for edges
		// slot for Octree
		// slot for triangles
			string name;
			

	};
	typedef Mesh& MeshReference;  // reference to a mesh
	typedef Mesh* MeshPTR; // pointer to a mesh
}

#endif // Mesh_HPP
