#include "StaticMesh.hpp"

StaticMeshDefinition::StaticMesh::StaticMesh()
{
	
}

StaticMeshDefinition::StaticMesh::~StaticMesh()
{
}

void StaticMeshDefinition::StaticMesh::uploadOffsetandScaleToGPU()
{
	StaticMeshShader.uploadOffsetVectorToGPU(this->offset);
	StaticMeshShader.uploadScaleFloatToGPU(this->scale);
}

void StaticMeshDefinition::StaticMesh::renderWithStaticColor(v4 color)
{
	StaticMeshShader.uploadStaticColorVectorToGPU(color);
	StaticMeshShader.setStaticColorBool(true);
	render();
	StaticMeshShader.setStaticColorBool(false);
}