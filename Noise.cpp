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

v3 Sculpting::Noising::ExtendLine(v3 CenterPoint, v3 CurrentPoint, float NoiseValueX, float NoiseValueY, float NoiseValueZ, float distanceX, float distanceY)
{

	v3 NoisePoint = CurrentPoint;
	//If we have 0 in the coordinates of the mesh simply change where 0 appeared.
	if (CurrentPoint.x == 0)
	{
		NoisePoint.x = NoiseValueX;
		NoisePoint.y = CurrentPoint.y;
		NoisePoint.z = CurrentPoint.z;
		return NoisePoint;
	}

	if (CurrentPoint.y == 0)
	{
		NoisePoint.x = CurrentPoint.x;
		NoisePoint.y = NoiseValueY;
		NoisePoint.z = CurrentPoint.z;
		return NoisePoint;
	}

	if (CurrentPoint.z == 0)
	{
		NoisePoint.x += CurrentPoint.x;
		NoisePoint.y = CurrentPoint.y;
		NoisePoint.z = NoiseValueZ;
		return NoisePoint;
	}
	//Using the two point line formula in three - dimensional coordinate system to find the linear equation between the Center Point with the selected Mesh Point.
	//Then we use the random X into the linear equation to get the Y and Z value. To get our point. Doing so makes every point on the mesh in the right direction.
	//If the distance < 0.3 than round it to 0, if not , the Y and Z value will become extreamly large.
	if (fabs(distanceX) <= 0.3) distanceX = 0;
	if (distanceX != 0)
	{

		float result = (NoiseValueX - CenterPoint.x) / (CurrentPoint.x - CenterPoint.x);
		NoisePoint.x = NoiseValueX;
		NoisePoint.y = result * (CurrentPoint.y - CenterPoint.y) + CenterPoint.y;
		NoisePoint.z = result * (CurrentPoint.z - CenterPoint.z) + CenterPoint.z;
		glm::vec3 cameraPos;
		return NoisePoint;

	}
	//If that happened ,use random Y to generate Z instead.
	if (fabs(distanceY) <= 0.08) distanceY = 0;
	if (distanceX == 0 && distanceY != 0)
	{

		float result = (NoiseValueY - CenterPoint.y) / (CurrentPoint.y - CenterPoint.y);
		NoisePoint.x = CurrentPoint.x;
		NoisePoint.y = NoiseValueY;
		NoisePoint.z = result * (CurrentPoint.z - CenterPoint.z) + CenterPoint.z;
		return NoisePoint;
	}
	else
	{
		NoisePoint.x = CurrentPoint.x;
		NoisePoint.y = CurrentPoint.y;
		NoisePoint.z = NoiseValueZ;
		return NoisePoint;
	}

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
			r = RandomDegree(60.0, 80.0);
		}
		else {
			r = RandomDegree(260.0, 280.0);
		}
		r = (r * float(3.14159)) / 180;
		float randomNum = sin(r) / 100;

		float NoiseValueX = randomNum + cMesh.vertices[element.first].position.x;
		float NoiseValueY = randomNum + cMesh.vertices[element.first].position.y;
		float NoiseValueZ = randomNum * 2 + cMesh.vertices[element.first].position.z;



		float distanceX = cMesh.vertices[element.first].position.x - cMesh.center.x;
		float distanceY = cMesh.vertices[element.first].position.y - cMesh.center.y;

		v3 noisePoint = ExtendLine(cMesh.center, cMesh.vertices[element.first].position, NoiseValueX, NoiseValueY, NoiseValueZ, distanceX, distanceY);
		cMesh.vertices[element.first].position = noisePoint;


	}




}
