#include "StaticMesh.hpp"
#include "MeshFileLoader.hpp"

using namespace MeshStatsDefinition;

StaticMeshDefinition::StaticMesh::StaticMesh()
{


}

StaticMeshDefinition::StaticMesh::~StaticMesh()
{
}

void StaticMeshDefinition::StaticMesh::bindStatic()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	// binding vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesMemorySize(), vertices.data(), GL_STATIC_DRAW);

	// binding indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleMemorySize(), static_cast<void*>(triangles.data()), GL_STATIC_DRAW);

	// enable position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)0);
	// enable color data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)offsetof(V3D, V3D::color)); // color data reserves 4 slots.
	// enable Normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)offsetof(V3D, V3D::normal)); // color data reserves 4 slots.

	unbindActiveVAO();
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
	this->bindStatic(); // this mesh is going to be only modified in the shader as it is static.
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