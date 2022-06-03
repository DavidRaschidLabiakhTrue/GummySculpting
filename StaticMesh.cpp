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
