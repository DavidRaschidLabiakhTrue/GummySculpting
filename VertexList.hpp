#ifndef VertexList_HPP
#define VertexList_HPP

#include "V3D.hpp"
#include "Indices.hpp"
#include <unordered_set>


namespace VertexListDefinition
{
	using namespace VertexDefinition;
	using namespace IndicesDefinition;

	using std::vector;

	// generalization of Vertex List mechanics
	// Inherited by GraphicsData -> MeshStats -> Mesh
	class VertexList
	{
	public:
		Construct VertexList();
		Deconstruct ~VertexList();

		RV3D getVertex(int index); // access element reference by index

		void setVertex(RV3D element, int index); // set element by index

		void colorDataUniformly(rv4 uniformColor);

		const int verticesMemorySize(); // returns the memory size of vertices allocate within the vertex list

		int verticeCount(); // returns the count of vertices in the vertex list

		Vertices vertices; //

		auto getVertexArray(); // get the underlying array component.

		vector<int> getTrianglesFromVertices(KeyList vertexIDs); // Get all triangles that contain any of the given vertices
	};

}

#endif