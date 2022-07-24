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
	const float conversionConstant = 3.14159f / 180.0f; // precompute the const
	forall(element, cMesh.currentVertices)
	{
		float r;
		seed++;
		if (seed % 2 == 0)
		{
			r = RandomDegree(80.0, 100.0);
		}
		else {
			r = RandomDegree(260.0, 280.0);
		}
		float randomNum = sin(r * conversionConstant);

		cMesh.vertices[element.first].position += payload.polarity * (randomNum * cMesh.vertices[element.first].normal) * 0.01f; // multiplication is faster than division 0.01 == 1/100

	}




}
