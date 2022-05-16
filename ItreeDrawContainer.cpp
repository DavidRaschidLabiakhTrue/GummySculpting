#include "ItreeDrawContainer.hpp"
#include "Shader.hpp"

using namespace ShaderDefinition;

ITreeDrawContainerDefinition::ItreeDrawContainer::ItreeDrawContainer()
{
}

ITreeDrawContainerDefinition::ItreeDrawContainer::~ItreeDrawContainer()
{
}

void ITreeDrawContainerDefinition::ItreeDrawContainer::bindContainer()
{
	say "binding ITreeDrawContainer" done;
	glGenVertexArrays(1, &gboITreeDrawContainer.vao);
	glGenBuffers(1, &gboITreeDrawContainer.vbo);
	glGenBuffers(1, &gboITreeDrawContainer.ebo);

	glBindVertexArray(gboITreeDrawContainer.vao);

	// binding vertices
	glBindBuffer(GL_ARRAY_BUFFER, gboITreeDrawContainer.vbo);
	glBufferData(GL_ARRAY_BUFFER, itreeDrawVertex.size() * sizeof(V3D), itreeDrawVertex.data(), GL_STATIC_DRAW);

	// binding indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gboITreeDrawContainer.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, itreeDrawIndices.size() * sizeof(KeyData), static_cast<void*>(itreeDrawIndices.data()), GL_STATIC_DRAW);

	// enable position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)0);
	// enable color data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)offsetof(V3D, V3D::color)); // color data reserves 4 slots.
}

void ITreeDrawContainerDefinition::ItreeDrawContainer::drawContainer()
{
	if (shoulddraw)
	{
		StandardShader.use();
		gboITreeDrawContainer.bindVAO();
		glDrawElements(GL_LINES, itreeDrawIndices.size(), GL_UNSIGNED_INT, NULL);
		unbindActiveVAO();
	}
}
