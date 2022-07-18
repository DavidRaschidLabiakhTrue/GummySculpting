#ifndef GraphicsBufferObjects_HPP
#define GraphicsBufferObjects_HPP

#include "Macro.hpp"
#include "OpenGLWrapper.hpp"
Usage Macros;

namespace GraphicsBufferObjectsDefinition
{
	Usage Macros;
	Usage GL;

	

	// OpenGL Buffer ID Values.
	// Inherited By Graphics Data -> Mesh Stats -> Mesh
	class GraphicsBufferObject
	{
		public:
		Construct GraphicsBufferObject();
		Deconstruct ~GraphicsBufferObject();

		void bindVAO(); // bind the VAO to the GPU to call it'd ID and begin rendering it.

		

		BufferID vao = 0; // vertex array buffer
		BufferID vbo = 0; // vertex buffer
		BufferID ebo = 0; // vertex element buffer
	};
	
}

#endif 
