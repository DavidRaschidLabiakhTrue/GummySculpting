#ifndef OpenGLWrapper_HPP
#define OpenGLWrapper_HPP

#include "glad/glad.h"
#include "Macro.hpp"
// wraps up abstract opengl functionality into a more succint and readable API.
namespace GL
{
	Usage Macros;
	typedef GLuint BufferID;

	extern const BufferID UnbindAllVAO; // Value to signify we are unbinding all VAOS.
	
	extern const GLsizei GenerateOneBuffer;

	extern inline void unbindActiveVAO(); // unbinds current VAO binding to GPU.
    extern inline void drawFilled();
	extern inline void drawLined();
	extern inline void set3DRenderingParameters();

	extern inline void printOpenGLEnviromentInfo();




	extern inline void bindVertexArray(BufferID id);
	extern inline void bindArrayBuffer(BufferID id);
	extern inline void bindElementArrayBuffer(BufferID id);
}

#endif // !OpenGLWrapper_HPP
