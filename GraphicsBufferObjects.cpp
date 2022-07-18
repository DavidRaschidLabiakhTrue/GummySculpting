#include "GraphicsBufferObjects.hpp"

Usage GraphicsBufferObjectsDefinition;



GraphicsBufferObject::GraphicsBufferObject()
{
}

GraphicsBufferObject::~GraphicsBufferObject()
{
}

void GraphicsBufferObject::bindVAO()
{
	glBindVertexArray(vao);
}

void GraphicsBufferObjectsDefinition::GraphicsBufferObject::deleteBuffers()
{
	glDeleteBuffers(1, &this->ebo);
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->vao);

	ebo = vbo = vao = 0; // set all to 0 for safety.
}
