#ifndef GraphicsData_HPP
#define GraphicsData_HPP

#include "TriangleList.hpp"

#include "GraphicsBufferObjects.hpp"

#include "VertexLookUp.hpp"

#include "EdgeList.hpp"

#include "TriangleLookUp.hpp"

namespace GraphicsDataDefinition
{
	using namespace TriangleListDefinition;
	using namespace VertexListDefinition;
	using namespace GraphicsBufferObjectsDefinition;
	using namespace VertexLookUpDefinition;
	using namespace EdgeListDefinition;
	using namespace TriangleLookUpDefinition;
	/*
		*	Graphics Data - A graphics format meant specifically for interacting with the GPU.
		*   Inherited by MeshStats -> Mesh
	*/
	class GraphicsData : protected GraphicsBufferObject, public TriangleLookUp
	{
		public:
			Construct GraphicsData();
			Deconstruct ~GraphicsData();

			void bind(); // bind to OpenGL

			void refresh(); // reload vertex data to OpenGL.

			void render(); // render and draw vertex data.

			void invertFaces();

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

