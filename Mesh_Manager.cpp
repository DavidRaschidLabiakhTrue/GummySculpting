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
		MeshFileExporter::exportStlFile(meshFilePath, getActiveMeshReference()); // oh there is STL. When did this get added?
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

void Mesh_Manager_Definition::Mesh_Manager::removeMesh(int whichToRemove)
{
}

void Mesh_Manager::setUpMeshResources()
{
	this->makeLastMeshActive();
}

bool Mesh_Manager_Definition::Mesh_Manager::thereIsMeshes()
{
	return meshes.size() > 0;
}

void Mesh_Manager_Definition::Mesh_Manager::switchMesh(SculptPayloadReference payload)
{
	if (meshes.size() <= 1)
	{
		return; // there is no point trying to switch meshes if none exist.
	}
	


	v3 closestHit = v3(2000000.0f); // impossible.
	MeshPTR switchedMesh = NULL;

	int i = 0;
	for (MeshList::iterator iter = meshes.begin(); iter != meshes.end(); ++iter)
	{
		if (&(*iter) == activeMesh)
		{
			continue;
		}

		(*iter).octreeRayIntersection(payload.selectionOrigin, payload.direction);
		if ((*iter).collision.isCollision)
		{
			if ((*iter).collision.distance <= glm::distance(closestHit, payload.selectionOrigin))
			{
				switchedMesh = &(*iter);
				closestHit = (*iter).collision.position;
			}
		}
		++i;
	}
	if (switchedMesh != NULL)
	{
		activeMesh->isActive = false;
		activeMesh = switchedMesh;
		activeMesh->isActive = true;
		activeMesh->rebuildOctree();
		say "Mesh Switched successfully" done;
	}
	else
	{
		say "Mesh Not switched successfully" done;
	}
	

}

void Mesh_Manager_Definition::Mesh_Manager::deleteCurrent()
{
	activeMesh->deleteBuffers();
	activeMesh->cleanUpMesh();

	for (auto iter = meshes.begin(); iter != meshes.end(); ++iter)
	{
		if (&(*iter) == activeMesh)
		{
			meshes.erase(iter);
			break;
		}
	}

	makeLastMeshActive();
}

void Mesh_Manager::makeLastMeshActive()
{
	if (meshes.size() != 0)
	{
		activeMesh = &meshes.back(); // assigns the last mesh in the list to the active processed mesh.
	}

	activeMesh->isActive = true;

	for (auto iter = meshes.begin(); iter != meshes.end(); ++iter)
	{
		if (&(*iter) != activeMesh)
		{
			(*iter).isActive = false;
			break;
		}
	}

}
