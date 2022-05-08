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
