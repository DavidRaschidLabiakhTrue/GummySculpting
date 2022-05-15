#include "MeshStats.hpp"
using namespace MeshStatsDefinition;

MeshStats::MeshStats()
{
}

MeshStats::~MeshStats()
{
}

/*
	Collect All Relevant Stats in a mesh linearly. 
*/
void MeshStats::collectStats()
{
	v3 max = v3(0);
	v3 min = v3(0);
	v3 tempCenter = v3(0);

	forall(vert, vertices)
	{
		center += vert.position;

		if (vert.position.x > max.x)
		{
			max.x = vert.position.x;
		}
		eif(vert.position.x < min.x)
		{
			min.x = vert.position.x;
		}


		if (vert.position.y > max.y)
		{
			max.y = vert.position.y;
		}
		eif(vert.position.y < min.y)
		{
			min.y = vert.position.y;
		}


		if (vert.position.z > max.z)
		{
			max.z = vert.position.z;
		}
		eif(vert.position.z < min.z)
		{
			min.z = vert.position.z;
		}
	}

	this->limMax = max;
	this->limMin = min;

	tempCenter = tempCenter / (float)verticeCount();

	this->center = tempCenter;
}
