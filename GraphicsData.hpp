#ifndef GraphicsData_HPP
#define GraphicsData_HPP

#include "TriangleList.hpp"
#include "VertexList.hpp"
#include "GraphicsBufferObjects.hpp"

Usage TriangleListDefinition;
Usage VertexListDefinition;
Usage GraphicsBufferObjectsDefinition;


namespace GraphicsDataDefinition
{
	/*
		*	Graphics Data - A graphics format meant specifically for interacting with the GPU.
		*   Inherited by MeshStats -> Mesh
	*/
	class GraphicsData : protected GraphicsBufferObject, public VertexList, public TriangleList
	{
		public:
			Construct GraphicsData();
			Deconstruct ~GraphicsData();

			void bind(); // bind to OpenGL

			void refresh(); // reload vertex data to OpenGL.

			void render(); // render and draw vertex data.


			

			// need to implement copy.

	};
	// preload any constants used for binding and refreshing
	namespace OpenGLVertexAttributes
	{
		extern const int SizeOfV3D;
		extern const int SizeOfv3;
		extern const int SizeOfv4;
		extern const int SizeOfKeyData;
		extern const int SizeOfVertex;

		extern const int SizeOfIndice;
	}
}
#endif // !GraphicsData_HPP

