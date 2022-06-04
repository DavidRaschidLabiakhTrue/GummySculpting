#include "Gizmo.hpp"

using namespace GizmoDefinition;

GizmoDefinition::Gizmo::Gizmo(bool trueConstructor)
{

}

StaticMesh GizmoDefinition::Gizmo::createGizmoMesh(string fileName, v4 color, v3 offset, float rotationAngle, v3 rotationAxis, float scale)
{
	StaticMesh newStaticMesh = StaticMesh();
	MeshFileLoader::loadGumFile(fileName, newStaticMesh, color, rotationAngle, rotationAxis);
	newStaticMesh.offset = offset;
	newStaticMesh.scale = scale;

	return newStaticMesh;
}

//Naive solution, only use on meshes with few tris
bool GizmoDefinition::Gizmo::detectMeshClick(StaticMesh sMesh)
{
	v2 unusedBaryPosition; // Unused variable to pass into the intersection function
	float tempDistance;

	forall(tri, sMesh.triangles)
	{
		if (intersectRayTriangle(
			this->origin().position,
			this->direction,
			sMesh.vertices[tri[0]].position * sMesh.scale + sMesh.offset,
			sMesh.vertices[tri[1]].position * sMesh.scale + sMesh.offset,
			sMesh.vertices[tri[2]].position * sMesh.scale + sMesh.offset,
			unusedBaryPosition,
			tempDistance))
		{
			return true;
		}
	}
	return false;
}
