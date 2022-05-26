#include "VertexList.hpp"

Usage VertexListDefinition;

VertexList::VertexList()
{
}
VertexList::~VertexList()
{
}
// sets the element by index
void VertexList::setVertex(RV3D element, int index)
{
    vertices[index] = element;
}
const int VertexList::verticesMemorySize()
{
    return (const int)vertices.size() * sizeof(V3D);
}
void VertexList::colorDataUniformly(rv4 uniformColor)
{
    int countOfVertices = (int)vertices.size();
    if (countOfVertices == 0)
    {
        // throw error, there are no vertices to color.
    }
    else
    {
        forall(vert, vertices)
        {
            vert.color = uniformColor;
        }
    }
}

int VertexList::verticeCount()
{
    return (int)vertices.size();
}

// returns the underlying vector array component.
// auto returned because figuring out this data type is a waste of time.
auto VertexList::getVertexArray()
{
    return vertices.data();
}

// gets the element referenece by index
RV3D VertexList::getVertex(int index)
{
    return vertices[index];
}

vector<int> VertexList::getTrianglesFromVertices(KeyList vertexIDs)
{
    unordered_set<int> triangleIDset;
    foreach (vertex, vertexIDs)
    {
        foreach (triangle, vertices[vertex].triangleIDs)
        {
            triangleIDset.insert(triangle);
        }
    }

    return vector<int>(triangleIDset.begin(), triangleIDset.end());
}