#include "Noise.hpp"

#include "glm/gtc/random.hpp"

#include "glm/gtc/noise.hpp"

using glm::linearRand;
using glm::perlin;
using glm::simplex;

#include "SculptAlgos.hpp"



void Sculpting::Noising::applyNoise(MeshReference cMesh, SculptPayloadReference payload, const int interations)
{
	auto& cHistory = cMesh.history.currentChangeLog;
	HistoryKeyVertexMap apply;

	const auto rMult = payload.radius * 0.5f * 0.3f * payload.hitNorm;
	const auto hitPoint = cMesh.collision.position + rMult;


	const auto rDir = payload.direction * -1.0f; // this flips all axis.




	Algos::storeCurrentElementsToMap(apply, cHistory, cMesh);
	
	// uncommand this to begin the algo
	//
	//for (int i = 0; i < interations; i++)
	//{
	//	forall(element, apply)
	//	{
	//		element.second.position; APPLY ALGO HERE
	//	}
	//}


	Algos::applyMapToMesh(apply, cMesh);

	cMesh.recomputeNormals(apply);


}
