#include "Cursor3D.hpp"
#include "MeshFileLoader.hpp"
#include "ToolsWindow.hpp"
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

void _Cursor3D::Cursor3D::drawCursor()
{

	CursorShader.use();
	CursorShader.uploadScaleFloatToGPU(ToolsWindowDefinition::RadiusSlider);
	CursorShader.uploadModelMatrixToGPU(this->model);
	CursorShader.uploadOffsetVectorToGPU(this->offset);
	render();
}
