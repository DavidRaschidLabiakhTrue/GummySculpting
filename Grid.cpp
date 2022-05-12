#include "Grid.hpp"

GridDefinition::Grid::Grid()
{

}

GridDefinition::Grid::Grid(bool trueConstructor)
{
	int gridResolution = 20;

	const int limit = gridResolution / 2;

	int indiceTracker = -1;

	for (int i = -(int)limit; i <= limit; i++)
	{
		this->vertices.emplace_back(v3(i, 0, limit));
		this->vertices.emplace_back(v3(i, 0, -limit));
		this->vertices.emplace_back(v3(limit, 0, i));
		this->vertices.emplace_back(v3(-limit, 0, i));



		this->indices.push_back(++indiceTracker);
		this->indices.push_back(++indiceTracker);
		this->indices.push_back(++indiceTracker);
		this->indices.push_back(++indiceTracker);


		if (i == 0)
		{
			this->vertices[indiceTracker].loadColorAs255(225, 0, 255);
			this->vertices[indiceTracker - 1].loadColorAs255(225, 0, 255);
			this->vertices[indiceTracker - 2].loadColorAs255(225, 255, 0);
			this->vertices[indiceTracker - 3].loadColorAs255(225, 255, 0);

		}
	}

	/*
	forall(indexpos, indices)
	{
		vertices[indexpos].printPosition();
	}
	*/

	vertices[0].loadColorAs255(225, 0, 0);
	vertices[1].loadColorAs255(225, 0, 0);
	vertices[2].loadColorAs255(225, 0, 0);
	vertices[3].loadColorAs255(225, 0, 0);



	vertices[vertices.size() - 1].loadColorAs255(225, 0, 0);
	vertices[vertices.size() - 2].loadColorAs255(225, 0, 0);
	vertices[vertices.size() - 3].loadColorAs255(225, 0, 0);
	vertices[vertices.size() - 4].loadColorAs255(225, 0, 0);

	bindGrid();
}

GridDefinition::Grid::~Grid()
{
}

void GridDefinition::Grid::bindGrid()
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesMemorySize(), static_cast<void*>(indices.data()), GL_STATIC_DRAW);

	// enable position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)0);
	// enable color data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)offsetof(V3D, V3D::color)); // color data reserves 4 slots.

	unbindActiveVAO();
}

void GridDefinition::Grid::drawGrid()
{
	if (shouldDrawGrid)
	{
		StandardShader.use();
		bindVAO();
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, NULL);
		unbindActiveVAO();
	}
}
