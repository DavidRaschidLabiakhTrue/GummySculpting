#include "OpenGLWrapper.hpp"

namespace GL
{
	const BufferID UnbindAllVAO = 0;
	const GLsizei GenerateOneBuffer = 1;
}

Usage GL;

 // signify to only generate 1 buffer.



void GL::set3DRenderingParameters()
{
	glEnable(GL_DEPTH_TEST); // we want depth test and later stencil
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	//glEnable(GL_MULTISAMPLE);
}

void GL::printOpenGLEnviromentInfo()
{
	const unsigned char* gpuStr = glad_glGetString(GL_VENDOR);
	const unsigned char* verStr = glad_glGetString(GL_VERSION);

	// This should generally be the only printf in this project. 
	printf("%s\n", gpuStr);
	printf("%s\n", verStr);
}

void GL::bindVertexArray(BufferID id)
{
	glBindVertexArray(id);
}

void GL::bindArrayBuffer(BufferID id)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void GL::bindElementArrayBuffer(BufferID id)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void GL::unbindActiveVAO()
{
	glBindVertexArray(UnbindAllVAO); // this seals off the entire binding process.
}
// wraps polygonmode filled drawing call
void GL::drawFilled()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
}
// wraps polygonmode line drawing call
void GL::drawLined()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// clears all depth information to allow objects to be drawn on top of currently drawn objects
void GL::clearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}