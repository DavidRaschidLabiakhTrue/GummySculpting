#ifndef Mesh_Manager_HPP
#define Mesh_Manager_HPP

#include "MeshFileLoader.hpp" // also includes "Mesh.h"

namespace Mesh_Manager_Definition
{
	Usage MeshDefinition;
	Usage MeshFileLoader;
	typedef vector<Mesh> MeshList;
	typedef int MeshLevel;
	// manages an array list of meshes
	// binds to GPU
	// Inherited by Renderer
	class Mesh_Manager
	{
		public:
			Construct Mesh_Manager();
			Deconstruct ~Mesh_Manager();

			MeshList meshes;

			MeshPTR activeMesh = UnassignedPTR; // likely need to make global.

			void makeLastMeshActive();
			void loadMeshFromFile(string meshFilePath); // load in a mesh from a file
			void bindAllMeshes();

			MeshPTR getActiveMesh();

			MeshReference getActiveMeshReference();


			

			

	};
}

#endif
