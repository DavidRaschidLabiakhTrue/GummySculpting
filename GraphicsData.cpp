#include "GraphicsData.hpp"

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

void GraphicsDataDefinition::GraphicsData::loadTriangleTest()
{
	V3D p1 = V3D(-1, -1, 0);
	V3D p2 = V3D(1, -1, 0);
	V3D p3 = V3D(1, 1, 0);

	vertices.push_back(p1);
	vertices.push_back(p2);
	vertices.push_back(p3);

	this->indices.push_back(0);
	this->indices.push_back(1);
	this->indices.push_back(2);

	IndexedTriangle tri;
	tri.indice[0] = 0;
	tri.indice[1] = 1;
	tri.indice[2] = 2;
	this->triangles.push_back(tri);
}

void GraphicsData::bind()
{
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	// binding vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_SIZING(vertices), vertices.data() , GL_STATIC_DRAW);

	// binding indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(IndexedTriangle), static_cast<void*>(triangles.data()), GL_STATIC_DRAW);

	// enable position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)0);
	// enable color data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)offsetof(V3D, V3D::color)); // color data reserves 4 slots.

	unbindActiveVAO();


}

void GraphicsData::refresh()
{
	glBindVertexArray(vao);

	// refresh vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_SIZING(vertices), vertices.data(), GL_STATIC_DRAW);

	// refresh indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(IndexedTriangle), triangles.data(), GL_STATIC_DRAW);
	// enable position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)0);
	// enable color data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)offsetof(V3D, V3D::color)); // color data reserves 4 slots.

	unbindActiveVAO();
}

void GraphicsData::render()
{
	bindVAO();

	glDrawElements(GL_TRIANGLES, triangles.size()*3, GL_UNSIGNED_INT, NULL);

	GL::unbindActiveVAO();
}
