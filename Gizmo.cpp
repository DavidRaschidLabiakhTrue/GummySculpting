#include "Gizmo.hpp"

using namespace GizmoDefinition;

GizmoDefinition::Gizmo::Gizmo() {}
GizmoDefinition::Gizmo::Gizmo(bool trueConstructor) {}
GizmoDefinition::Gizmo::~Gizmo() {}

StaticMesh GizmoDefinition::Gizmo::createGizmoMesh(string fileName, v4 color, v3 offset, float rotationAngle, v3 rotationAxis, float scale, bool invertFaces)
{
	StaticMesh newStaticMesh = StaticMesh(); // you can do auto newStaticMesh = StaticMesh() or just StaticMesh newStaticMesh. Either calls the default constructor.
	MeshFileLoader::loadGumFile(fileName, newStaticMesh, false);

	//Apply color
	newStaticMesh.colorDataUniformly(color);

	//Rotate
	glm::mat4 rotationMtx(1);
	rotationMtx = glm::rotate(rotationMtx, rotationAngle, rotationAxis);
	forall(vert, newStaticMesh.vertices)
	{
		vert.position = v3(rotationMtx * v4(vert.position, 1.0));
	}

	//Apply offset and scale
	newStaticMesh.offset = offset;
	newStaticMesh.scale = scale;

	//optionally invert all faces
	if (invertFaces)
	{
		newStaticMesh.invertFaces();
	}

	//Send to GPU
	newStaticMesh.collectStats();
	newStaticMesh.bind(); // this mesh is going to be only modified in the shader as it is static.

	return newStaticMesh;
}

//Naive solution, only use on meshes with few tris
bool GizmoDefinition::Gizmo::detectMeshClick(StaticMeshReference sMesh)
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

void GizmoDefinition::Gizmo::draw()
{
	forall(handle, handles)
	{
		handle->mesh.uploadOffsetandScaleToGPU();
		if (handle->axis == activeAxis)
		{
			handle->mesh.renderWithStaticColor(GizmoColors::lightOrange);
		}
		else if (handle->hovered) {
			handle->mesh.renderWithStaticColor(handle->hoverColor);
		}
		else {
			handle->mesh.render();
		}
	}
}

void GizmoDefinition::Gizmo::clearHover()
{
	forall(handle, handles)
	{
		handle->hovered = false;
	}
}

void GizmoDefinition::Gizmo::checkClicked() {
	clicked = cast();
	if (!clicked)
	{
		screenToWorld();
		active = false;
		activeAxis = GizmoAxis::NONE;
	}
}