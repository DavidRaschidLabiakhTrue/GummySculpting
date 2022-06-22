#include "StaticCircle.hpp"

StaticCircleDefinition::StaticCircle::StaticCircle()
{

}

StaticCircleDefinition::StaticCircle::StaticCircle(bool trueConstructor)
{
	const int circleResolution = 360;

	float heading;

	this->radius = this->diameter / 2.0f;

	for (int i = 0; i < circleResolution; i++)
	{
		heading = radians((float)i);

		this->vertices.emplace_back(V3D(v3(cos(heading) * diameter, sin(heading) * diameter, 0.0f)));
	}

	for (int i = 0; i < circleResolution; i++)
	{
		this->indices.emplace_back(i);
		this->indices.emplace_back(i + 1);
	}
	this->indices[(this->indices.size() - 1)] = 0; // complete the circle

	collectStats();

	this->bindCircle();
}

void StaticCircleDefinition::StaticCircle::bindCircle()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	refreshCircle();
}

void StaticCircleDefinition::StaticCircle::refreshCircle()
{
	glBindVertexArray(vao);

	// binding vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesMemorySize(), vertices.data(), GL_STATIC_DRAW);

	// binding indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesMemorySize(), static_cast<void*>(indices.data()), GL_STATIC_DRAW);

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




void StaticCircleDefinition::StaticCircle::drawCircle()
{
		CircleShader.use();
		CircleShader.uploadTimeToGPU();
		bindVAO();
		glDrawElements(GL_LINES, (GLsizei)indices.size(), GL_UNSIGNED_INT, NULL);
		unbindActiveVAO();
}

StaticCircleDefinition::StaticCircle::~StaticCircle()
{

}
