#include "Octant.hpp"

using namespace OctantDefinition;


Octant::Octant()
{
	// empty
}

Octant::Octant(v3 center, double halfsize, int limit, int index)
{
	octantLimit = limit;
	octantIndex = index;
	octantCenter = center;
	octantHalfSize = halfsize;

}

Octant::~Octant()
{

}

bool Octant::insert(TriangleAndOctantPairList& list, TriangleID id)
{
	this->triangleIDs.emplace_back(id);
	list[id].octantIndex = this->octantIndex;
	return triangleIDs.size() > octantLimit;
}

OctantList Octant::subdivide(OctantIndex octantsIndex, double looseness)
{
	const double childHalfSize = looseness / 2.0f;
	OctantList newOctants;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				double x = (octantCenter.x - childHalfSize) + i * octantHalfSize;
				x = x + (1 - 2 * i) * childHalfSize * looseness;
				double y = (octantCenter.y - childHalfSize) + j * octantHalfSize;
				y = y + (1 - 2 * j) * childHalfSize * looseness;
				double z = (octantCenter.z - childHalfSize) + k * octantHalfSize;
				z = z + (1 - 2 * k) * childHalfSize * looseness;

				// Add child to children and octants arrays, always last in array
				children[i * 4 + j * 2 + k] = octantsIndex;
				newOctants.emplace_back(Octant(v3(x, y, z), childHalfSize * (1 + looseness), octantLimit, octantsIndex++));
				newOctants[newOctants.size() - 1].parent = this->octantIndex;
			}
		}
	}
	return newOctants;
}









/*
* 
#include "Octant.hpp"



bool Octant::inBounds(vector<int> &points)
{
    foreach (p, points)
    {
        v3 pos = getVertexPosition(p);
        if (abs(center.x - pos.x) > halfsize + std::numeric_limits<float>::epsilon() ||
            abs(center.y - pos.y) > halfsize + std::numeric_limits<float>::epsilon() ||
            abs(center.z - pos.z) > halfsize + std::numeric_limits<float>::epsilon())
        {
            return false;
        }
    }

    return true;
}

}

*/
/*
vector<v3> Octant::generateMesh()
{
    /**
     * Octant corner vertices visualization
     *    7-----6
     *   /|    /|
     *  3-----2 |
     *  | 4---|-5
     *  |/    |/
     *  0-----1
     *
     */
/*
    vector<v3> corners = {
        v3(center.x - halfsize, center.y - halfsize, center.z - halfsize),
        v3(center.x + halfsize, center.y - halfsize, center.z - halfsize),
        v3(center.x + halfsize, center.y + halfsize, center.z - halfsize),
        v3(center.x - halfsize, center.y + halfsize, center.z - halfsize),
        v3(center.x - halfsize, center.y - halfsize, center.z + halfsize),
        v3(center.x + halfsize, center.y - halfsize, center.z + halfsize),
        v3(center.x + halfsize, center.y + halfsize, center.z + halfsize),
        v3(center.x - halfsize, center.y + halfsize, center.z + halfsize)};

    vector<v3> verts = {
        corners[0], corners[1],
        corners[1], corners[2],
        corners[2], corners[3],
        corners[3], corners[0],
        corners[4], corners[5],
        corners[5], corners[6],
        corners[6], corners[7],
        corners[7], corners[4],
        corners[0], corners[4],
        corners[1], corners[5],
        corners[2], corners[6],
        corners[3], corners[7]};

    return verts;
}

*/

