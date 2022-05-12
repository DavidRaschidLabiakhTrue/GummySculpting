#include "Mesh_Manager.hpp"

using namespace Mesh_Manager_Definition;



Mesh_Manager::Mesh_Manager()
{

}

Mesh_Manager::~Mesh_Manager()
{

}

void Mesh_Manager::loadMeshFromFile(string meshFilePath)
{
	Mesh mesh;
	string fileType = meshFilePath.substr(meshFilePath.size() - 4, meshFilePath.size());

	if (fileType == ".gum" )
	{
		//mesh.loadTriangleTest();
		MeshFileLoader::loadGumFile(meshFilePath, mesh);
		meshes.push_back(mesh);
		return;
	}
	else
	{
		say "Error: cannot load .gum from Mesh_Manager::loadMeshFromFile" done;
		// raise error
	}
	
	
	
}

MeshPTR Mesh_Manager_Definition::Mesh_Manager::getActiveMesh()
{
	if (activeMesh == UnassignedPTR)
	{
		say "Assign the Mesh Dumb Ass" done;
		return UnassignedPTR;
	}
	return activeMesh;
}

void Mesh_Manager::bindAllMeshes()
{
	say "Binding All Meshes" done;

	forall(mesh, meshes)
	{
		mesh.generateEdges();
		mesh.bind();
	}

	this->makeLastMeshActive();
}

void Mesh_Manager::makeLastMeshActive()
{
	if (meshes.size() != 0)
	{
		activeMesh = &meshes.back(); // assigns the last mesh in the list to the active processed mesh.
	}
}
