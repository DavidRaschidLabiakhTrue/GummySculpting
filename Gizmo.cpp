#include "Gizmo.hpp"

using namespace GizmoDefinition;

GizmoDefinition::Gizmo::Gizmo(bool trueConstructor)
{

}

StaticMesh GizmoDefinition::Gizmo::CreateGizmoMesh(string fileName, v4 color, v3 offset, float rotationAngle, v3 rotationAxis, float scale)
{
	StaticMesh newStaticMesh = StaticMesh();
	MeshFileLoader::loadGumFile(fileName, newStaticMesh, color, rotationAngle, rotationAxis);
	newStaticMesh.offset = offset;
	newStaticMesh.scale = scale;

	return newStaticMesh;
}