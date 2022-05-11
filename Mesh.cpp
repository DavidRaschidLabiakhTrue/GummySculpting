#include "Mesh.hpp"
#include <limits>

using namespace MeshDefinition;


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
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
				result = findClosest(testCoordinate, tri[0], tri[1], tri[2]);
			}
			// there was a hit.
		}
		

	}
	
    return result;
}
