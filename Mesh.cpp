#include "Mesh.hpp"
#include <limits>

using namespace MeshDefinition;

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void MeshDefinition::Mesh::generateGraphsAndTrees()
{
    this->generateEdges();
    this->itreeGenerate();
    this->generateITreeVisualization();

    // Debugging/Testing Octree
    this->buildOctree();
	this->testOctree();
	// End Debugging/Testing Octree
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
