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
    this->octreePrintStats();

	// Testing Intersection and Collection
    v3 rayOrigin(0, 0, 3);
    v3 rayDirection(0, 0, -1);
    OctreeCollision collision = this->octreeRayIntersection(rayOrigin, rayDirection);
    if (collision.isCollision)
    {
        say "Collision: " done;
        say "\tRay Origin: " << to_string(rayOrigin) done;
        say "\tRay Direction: " << to_string(rayDirection) done;
        say "\tIntersected Triangle: "
            << collision.triangleID << "\n\t\t< "
            << glm::to_string(vertices[triangles[collision.triangleID][0]].position) << ", "
            << glm::to_string(vertices[triangles[collision.triangleID][1]].position) << ", "
            << glm::to_string(vertices[triangles[collision.triangleID][2]].position) << " >" done;
        say "\tIntersection Point: " << glm::to_string(collision.position) done;
        double collectRange = glm::sqrt(2);
        KeyList verticesCollected = collectVerticesAroundCollision(collision, collectRange);
        say "\tVertices Around Collision (Range " << collectRange << "): " << verticesCollected.size();
        for (int i = 0; i < verticesCollected.size(); i++)
        {
			say (i%20 == 0 ? "\n\t\t" : "") << verticesCollected[i] << " ";
        }
        say endl;
    }

	// Testing removal
	int count = 0;
	foreach(octant, octants) {
		count += (int) octant.triangleIDs.size();
	}
	say "Triangles in Octree: " << count done;

	for(int i = 0; i < totalTriangles(); i++)
	{
		removeTriangleFromOctree(i);
	}
	count = 0;
	foreach(octant, octants) {
		count += (int) octant.triangleIDs.size();
	}
	say "Triangles in Octree after Removal: " << count done;
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
