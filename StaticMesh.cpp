#include "StaticMesh.hpp"

using namespace MeshStatsDefinition;

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

v3 StaticMeshDefinition::StaticMesh::getTrueCenter()
{
	return this->center * this->scale + this->offset;
}