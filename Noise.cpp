#include "Noise.hpp"

#include "glm/gtc/random.hpp"

#include "glm/gtc/noise.hpp"

using glm::linearRand;
using glm::perlin;
using glm::simplex;

#include "SculptAlgos.hpp"

float Sculpting::Noising::RandomDegree(float range_min, float range_max) {
	float fraction = (float)rand() / RAND_MAX;
	return range_min + fraction * (range_max - range_min);
}

void Sculpting::Noising::applyNoise(MeshReference cMesh, SculptPayloadReference payload, const int interations)
{


	const auto rMult = payload.radius * 0.5f * 0.3f * payload.hitNorm;
	const auto hitPoint = cMesh.collision.position + rMult;


	const auto rDir = payload.direction * -1.0f; // this flips all axis.






	int seed = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	forall(element, cMesh.currentVertices)
	{
		float r;
		seed++;
		// element.first is an id value that accesses the vertices of any vertice we collected from octree
		// element.second is the vertice itself copied.
		//
		// // See smoothing and coloring
		//
		//cMesh.vertices[element.first] = ... // Apply the algo here.
		if (seed % 2 == 0)
		{
			r = RandomDegree(80.0, 100.0);
		}
		else {
			r = RandomDegree(260.0, 280.0);
		}
		r = (r * float(3.14159)) / 180;
		float randomNum = sin(r);

		cMesh.vertices[element.first].position.x += (randomNum * cMesh.vertices[element.first].normal.x) / 100;
		cMesh.vertices[element.first].position.y += (randomNum * cMesh.vertices[element.first].normal.y) / 100;
		cMesh.vertices[element.first].position.z += (randomNum * cMesh.vertices[element.first].normal.z) / 100;


	}




}
