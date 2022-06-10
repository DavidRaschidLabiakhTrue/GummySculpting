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

			void bindStatic();
			void initialize(StaticMesh& mesh, string fileName, v4 color, v3 offset, float scale, float rot, v3 rotAxis);

			void uploadOffsetandScaleToGPU();

			

			void renderWithStaticColor(v4 color);
			
			v3 getTrueCenter();

			v3 offset = v3(0); // offset it is to be rendered in the shader.
			float scale = 1.0f; // scale of the mesh
	};

	typedef StaticMesh& StaticMeshReference;
}

#endif
