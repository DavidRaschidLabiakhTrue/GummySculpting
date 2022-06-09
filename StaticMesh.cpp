#include "StaticMesh.hpp"
#include "MeshFileLoader.hpp"

using namespace MeshStatsDefinition;

StaticMeshDefinition::StaticMesh::StaticMesh()
{
	
}

StaticMeshDefinition::StaticMesh::~StaticMesh()
{
}

void StaticMeshDefinition::StaticMesh::initialize(StaticMesh& mesh, string fileName, v4 color, v3 offset, float scale, float rot, v3 rotAxis)
{
	MeshFileLoader::loadGumFile(fileName, mesh);

	//Apply color
	colorDataUniformly(color);

	//Should use modelMatrix but the staticMesh shader is not applying them properly yet
	m4 rotationMtx = glm::rotate(rot, rotAxis);
	forall(vert, this->vertices)
	{
		vert.position = v3(rotationMtx * v4(vert.position, 1.0));
	}

	this->offset = offset;
	this->scale = scale;

	//Send to GPU
	this->collectStats();
	this->bind(); // this mesh is going to be only modified in the shader as it is static.
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