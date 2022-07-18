#ifndef Mesh_Manager_HPP
#define Mesh_Manager_HPP

#include "MeshFileLoader.hpp" // also includes "Mesh.h"
#include "MeshFileExporter.hpp"

#include <list>

#include "SculptPayload.hpp"

namespace Mesh_Manager_Definition
{
	Usage MeshDefinition;
	Usage MeshFileLoader;
	Usage MeshFileExporter;
	using SculptPayloadDefinition::SculptPayloadReference;
	typedef std::list<Mesh> MeshList;
	//typedef vector<Mesh> MeshList;
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
			void exportMeshToFile(string meshFilePath); // export mesh to a file
			void setUpMeshResources();
			bool thereIsMeshes();
			void switchMesh(SculptPayloadReference payload);

			MeshPTR getActiveMesh();

			MeshReference getActiveMeshReference();

			void removeMesh(int whichToRemove);



			

	};
}

#endif
