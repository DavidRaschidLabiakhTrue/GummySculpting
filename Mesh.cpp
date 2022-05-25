#include "Mesh.hpp"
#include <limits>

using namespace MeshDefinition;

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::createVariableMap()
{
    meshVariables.emplace("octreedepthlimit", ref(octreeDepthLimit));
	meshVariables.emplace("octanttrianglelimit", ref(octantTriangleLimit));
	meshVariables.emplace("octreebuffer", ref(octreeBuffer));
	meshVariables.emplace("octreelooseness", ref(octreeLooseness));

}

void MeshDefinition::Mesh::generateGraphsAndTrees()
{
    this->generateEdges();
    collectStats();
    this->buildOctree();
}

KeyData Mesh::searchLinear(rv3 direction, rv3 origin)
{
    const int trianglecount = totalTriangles();
    KeyData result = ImpossibleKey;
    v3 testCoordinate = v3(numeric_limits<float>::max());

    v3 storedCoordinate = testCoordinate;

    for (int i = 0; i < trianglecount; i++)
    {
        auto tri = triangles[i];
        if (intersectionMoller(origin, direction, vertices[tri[0]].position, vertices[tri[1]].position, vertices[tri[2]].position, testCoordinate))
        {
            if (distance(testCoordinate, origin) < distance(storedCoordinate, origin))
            {
                storedCoordinate = testCoordinate;
                result = closest(testCoordinate, tri);
            }
            // there was a hit.
        }
    }

    return result;
}



void MeshDefinition::Mesh::undoHistory()
{
}

void MeshDefinition::Mesh::redoHistory()
{
}

void MeshDefinition::Mesh::cullHistory(ChangeLogLevel levelsUpwardToCull)
{
}
