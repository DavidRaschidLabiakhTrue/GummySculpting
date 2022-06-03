#ifndef StaticMesh_HPP
#define StaticMesh_HPP

#include "MeshStats.hpp"

#include "Shader.hpp"

namespace StaticMeshDefinition
{
	using namespace MeshStatsDefinition;
	using namespace ShaderDefinition;

	// these meshes do not deform at all.
	class StaticMesh : public MeshStats
	{
		public:
			StaticMesh();
			~StaticMesh();

			void uploadOffsetandScaleToGPU();

			v3 offset = v3(0); // offset it is to be rendered in the shader.
			float scale = 1.0f; // scale of the mesh

		
	};

	typedef StaticMesh& StaticMeshReference;
}

#endif
