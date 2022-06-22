#include "RayCasting.hpp"

#include "Window_API.hpp"

#include "Camera.hpp"
#include "Shader.hpp"

#include "LinearAlgebra.hpp"

#include "KeyInput.hpp"

#include "TopologyComputation.hpp"

using namespace RayCastDefinition;
using namespace Window_API;
using namespace CameraDefinition;

using namespace LinearAlgebra;

using namespace KeyInputDefinition;

using namespace ShaderDefinition;

RayCast::RayCast()
{

	V3D castPoint;
	castPoint.setPositionToCenter();
	castPoint.loadColorAs255(150, 81, 27); // magic numbers for a shader of orange
	this->vertices.push_back(castPoint);
	this->vertices.push_back(castPoint);
	this->indices.push_back(0);
	this->indices.push_back(1);

}

RayCastDefinition::RayCast::RayCast(bool trueConstruct)
{
	V3D castPoint;
	castPoint.setPositionToCenter();
	castPoint.loadColorAs255(150, 81, 27); // magic numbers for a shader of orange
	this->vertices.push_back(castPoint);
	this->vertices.push_back(castPoint);
	this->indices.push_back(0);
	this->indices.push_back(1);


	if (shouldDrawRay)
	{
		bindRay();
	}
}

RayCast::~RayCast()
{

}

bool RayCastDefinition::RayCast::cast()
{
	auto& io = ImGui::GetIO();
	if (!io.WantCaptureMouse && !CheckIfAnyKeyHeld() && CheckMouseHeld(GLFW_MOUSE_BUTTON_LEFT))
	{
		screenToWorld();
		return true;
	}
	return false;
}


void RayCast::bindRay()
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

void RayCastDefinition::RayCast::refreshRay()
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
}


void RayCastDefinition::RayCast::drawRay()
{

	if (shouldDrawRay)
	{
		bindVAO();
		glDrawElements(GL_LINES, (GLsizei) indices.size(), GL_UNSIGNED_INT, NULL);
		unbindActiveVAO();
	}

}



void RayCastDefinition::RayCast::screenToWorld()
{
	const auto scrn = WinAPI.reload(); // get current state of window data

	v3 spaceTranslationVector = v3(scrn.msx, (float)scrn.height - scrn.msy, 0 / GlobalCamera->farPlane);

	auto unprojection = unProject(spaceTranslationVector, GlobalCamera->view, GlobalCamera->projection, scrn.translationVector);
	setOrigin();
	direction = normalize(unprojection - vertices[0].position); // unprojection - the origin
	setEnd();


	if (shouldDrawRay)
	{

		refreshRay();
	}


}

void RayCastDefinition::RayCast::setOrigin()
{
	vertices[0].position = GlobalCamera->pos;
}

void RayCastDefinition::RayCast::setEnd(float length)
{
	vertices[1].position = vertices[0].position + direction * v3(length);
}

RV3D RayCastDefinition::RayCast::origin()
{
	return vertices[0];
}

RV3D RayCastDefinition::RayCast::end()
{
	return vertices[1];
}
