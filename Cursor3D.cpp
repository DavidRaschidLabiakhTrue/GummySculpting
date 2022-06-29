#include "Cursor3D.hpp"
#include "MeshFileLoader.hpp"

_Cursor3D::Cursor3D::Cursor3D()
{
}

_Cursor3D::Cursor3D::Cursor3D(bool trueConstructor)
{
	StaticMesh tMesh;
	MeshFileLoader::loadGumFile("smoothSphere.gum", tMesh);

	this->vertices = tMesh.vertices;
	this->triangles = tMesh.triangles;

	this->bindStatic();
	this->collectStats();
}

_Cursor3D::Cursor3D::~Cursor3D()
{
}
