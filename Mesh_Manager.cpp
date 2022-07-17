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
		makeLastMeshActive();
		return;
	}
	else if (fileType == ".obj")
	{
		MeshFileLoader::loadObjFile(meshFilePath, mesh);
		meshes.push_back(mesh);
		makeLastMeshActive();
		return;
	}
	else
	{
		say "Error: cannot load .gum from Mesh_Manager::loadMeshFromFile" done;
		// raise error
	}



}

void Mesh_Manager::exportMeshToFile(string meshFilePath)
{
	string fileType = meshFilePath.substr(meshFilePath.size() - 4, meshFilePath.size());

	if (fileType == ".gum")
	{
		MeshFileExporter::exportGumFile(meshFilePath, getActiveMeshReference());
		return;
	}
	else if(fileType == ".stl")
	{
		MeshFileExporter::exportStlFile(meshFilePath, getActiveMeshReference());
	}
	else
	{
		say "Error: unsupported file type" done;
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

MeshReference Mesh_Manager_Definition::Mesh_Manager::getActiveMeshReference()
{
    return *activeMesh;
}

void Mesh_Manager::setUpMeshResources()
{
	this->makeLastMeshActive();
}

void Mesh_Manager::makeLastMeshActive()
{
	if (meshes.size() != 0)
	{
		activeMesh = &meshes.back(); // assigns the last mesh in the list to the active processed mesh.
	}
}
