#include "GraphicsData.hpp"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
namespace GraphicsDataDefinition::OpenGLVertexAttributes
{
	const int SizeOfV3D = sizeof(V3D);
	const int SizeOfv3 = sizeof(v3);
	const int SizeOfv4 = sizeof(v4);
	const int SizeOfKeyData = sizeof(KeyData);
	const int SizeOfVertex = sizeof(V3D);
	const int SizeOfIndice = sizeof(KeyData);
}

Usage GraphicsDataDefinition;





#define INDICE_SIZING(x) (x).size() * OpenGLVertexAttributes::SizeOfIndice
#define VERTEX_SIZING(x) (x).size() * OpenGLVertexAttributes::SizeOfVertex
#define VEC3_SIZING(x) (x).size() * OpenGLVertexAttributes::SizeOfv3
#define VEC4_SIZING(x) (x).size() * OpenGLVertexAttributes::SizeOfv4
#define GLUINT_SIZING(x) (x).size() * OpenGLVertexAttributes::SizeOfKeyData

GraphicsData::GraphicsData()
{
}

GraphicsData::~GraphicsData()
{
}



void GraphicsData::bind()
{
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	// binding vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesMemorySize(), vertices.data(), GL_STREAM_DRAW);

	// binding indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleMemorySize(), static_cast<void*>(triangles.data()), GL_STREAM_DRAW);

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

void GraphicsData::refresh()
{
	glBindVertexArray(vao);

	// refresh vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_SIZING(vertices), vertices.data(), GL_STREAM_DRAW);

	// refresh indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleMemorySize(), static_cast<void*>(triangles.data()), GL_STREAM_DRAW);
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

void GraphicsData::render()
{
	bindVAO();

	glDrawElements(GL_TRIANGLES, triangleCountAsindiceCount(), GL_UNSIGNED_INT, NULL); // this is what actually draws to the screen

	GL::unbindActiveVAO();
}
